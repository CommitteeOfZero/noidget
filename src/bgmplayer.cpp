#include "vendor/dr_mp3.h"

#include "bgmplayer.h"

#include <QFile>

BgmPlayer::BgmPlayer(QObject* parent) : QObject(parent) {
    haveDecoder = false;
    haveDevice = false;
    playing = false;
}

BgmPlayer::~BgmPlayer() {
    if (haveDevice) mal_device_uninit(&device);
    if (haveDecoder) mal_decoder_uninit(&decoder);
}

void BgmPlayer::setBgm(const QString& path, uint32_t loopStart,
                       uint32_t loopEnd) {
    if (haveDevice) {
        mal_device_uninit(&device);
        haveDevice = false;
    }
    if (haveDecoder) {
        mal_decoder_uninit(&decoder);
        haveDecoder = false;
    }
    playing = false;

    emit bgmAvailabilityChanged(false);

    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        return;
    }
    file = f.readAll();

    mal_result result = mal_decoder_init_memory_mp3(
        file.constData(), file.size(), NULL, &decoder);
    if (result != MAL_SUCCESS) return;

    deviceConfig = mal_device_config_init_playback(
        decoder.outputFormat, decoder.outputChannels, decoder.outputSampleRate,
        &onSend);

    result = mal_device_init(NULL, mal_device_type_playback, NULL,
                             &deviceConfig, this, &device);
    if (result != MAL_SUCCESS) {
        mal_decoder_uninit(&decoder);
        return;
    }

    result = mal_device_start(&device);
    if (result != MAL_SUCCESS) {
        mal_device_uninit(&device);
        mal_decoder_uninit(&decoder);
        return;
    }

    loopPointStart = loopStart;
    loopPointEnd = loopEnd;
    framesPlayed = 0;

    haveDecoder = true;
    haveDevice = true;
    playing = true;

    emit bgmAvailabilityChanged(true);
}

mal_uint32 BgmPlayer::onSend(mal_device* pDevice, mal_uint32 frameCount,
                             void* pSamples) {
    BgmPlayer* player = (BgmPlayer*)pDevice->pUserData;
    if (!player->haveDecoder) return 0;

    uint32_t framesToRead = frameCount;
    if (player->loopPointEnd > 0) {
        framesToRead =
            qMin(frameCount, player->loopPointEnd - player->framesPlayed);
    }
    mal_uint32 result =
        (mal_uint32)mal_decoder_read(&player->decoder, framesToRead, pSamples);
    mal_uint32 framesLeft = frameCount - result;
    if (framesLeft > 0) {
        mal_decoder_seek_to_frame(&player->decoder, player->loopPointStart);
        player->framesPlayed =
            mal_decoder_read(&player->decoder, framesToRead, pSamples);
        result += player->framesPlayed;
        player->framesPlayed += player->loopPointStart;
    } else {
        player->framesPlayed += result;
    }

    return result;
}

void BgmPlayer::togglePaused() {
    if (!haveDecoder || !haveDevice) return;

    if (playing) {
        mal_device_stop(&device);
        playing = false;
    } else {
        mal_device_start(&device);
        playing = true;
    }
}