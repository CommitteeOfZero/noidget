#pragma once

#include "txstream.h"
#include <QObject>
#include <QFile>
extern "C" {
#include <xdelta3.h>
}

/*^jsdoc
 * Xdelta3 decode stream builder
 *
 * Xdelta3 streams are **not seekable**.
 * 
 * @class TxXdelta3Stream
 * @extends ng.tx.TxStream
 * @memberof ng.tx
 * @static
 * @toplevel
 * @hideconstructor
 * @property {string} srcPath - path to input file to be patched
 * @property {string} diffPath - path to VCDIFF patch
 ^jsdoc*/
class TxXdelta3Stream : public TxStream {
    Q_OBJECT
    Q_PROPERTY(QString srcPath READ srcPath WRITE setSrcPath)
    Q_PROPERTY(QString diffPath READ diffPath WRITE setDiffPath)

   public:
    explicit TxXdelta3Stream() : TxStream() {}
    ~TxXdelta3Stream() {}
    void open() override;
    void close() override;
    void seek(qint64 count) override;
    qint64 read(void* buffer, qint64 max) override;

    QString srcPath() { return _srcPath; }
    void setSrcPath(const QString& srcPath) { _srcPath = srcPath; }
    QString diffPath() { return _diffPath; }
    void setDiffPath(const QString& diffPath) { _diffPath = diffPath; }

   private:
    QString _srcPath, _diffPath;
    QFile *_srcFile = 0, *_diffFile = 0;
    void *_srcBuffer = 0, *_diffBuffer = 0;

    void* _outBuffer = 0;
    qint64 _outBytesAvailable = 0;

    bool _xd3NeedsInput;
    bool _inputAvailable;

    xd3_stream _xd3stream;
    xd3_config _xd3config;
    xd3_source _xd3source;

    void readUntilOutput();
};