#pragma once

#include "vendor/mini_al.h"

#include <QObject>
#include <QString>
#include <QByteArray>

class BgmPlayer : public QObject {
    Q_OBJECT

   public:
    explicit BgmPlayer(QObject* parent = 0);
    ~BgmPlayer();

    void setBgm(const QString& path);
    void togglePaused();

   signals:
    void bgmAvailabilityChanged(bool available);

   private:
    static mal_uint32 onSend(mal_device* pDevice, mal_uint32 frameCount,
                             void* pSamples);

    // Careful with accessing these - onSend runs on a background thread

    QByteArray file;
    bool haveDecoder;
    bool haveDevice;
    bool playing;
    mal_decoder decoder;
    mal_device device;
    mal_device_config deviceConfig;
};