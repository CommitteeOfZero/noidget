#include "writestreamaction.h"
#include "installerapplication.h"
#include "fs.h"
#include <util/exception.h>
#include <QDir>
#include <QDirIterator>

static const qint64 bufferSize = 1024 * 1024;

void WriteStreamAction::run() {
    QString dest = ngApp->globalFs()->expandedPath(_dest);
    QFile out(dest);
    if (!out.open(QIODevice::WriteOnly)) {
        throw NgException(QString("Could not write file: %1").arg(dest));
    }
    void* buffer = malloc(bufferSize);
    qint64 bytesToRead = _count;
    if (_count <= 0) bytesToRead = bufferSize;
    qint64 bytesRead = 0;
    while ((bytesRead = _stream->read(buffer, qMin(bytesToRead, bufferSize))) >
           0) {
        if (_isCancelled) {
            break;
        }
        out.write((const char*)buffer, bytesRead);
        _progress += bytesRead;
        if (_count > 0) {
            emit progress(_progress);
            bytesToRead -= bytesRead;
        }
    }
    if (_isCancelled) {
        emit log(QString("Stream write to %1 aborted mid-write after user "
                         "cancelled transaction")
                     .arg(dest));
    }
}