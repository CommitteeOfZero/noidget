#include "txfilestream.h"
#include <util/exception.h>
#include "installerapplication.h"
#include "fs.h"

void TxFileStream::open() {
    QString expandedPath = ngApp->globalFs()->expandedPath(_inPath);
    if (_inFile != nullptr) {
        throw NgException(
            QString("Tried to open file twice: %1").arg(expandedPath));
    }
    _inFile = new QFile(expandedPath, this);
    if (!_inFile->open(QIODevice::ReadOnly)) {
        throw NgException(QString("Couldn't open file: %1").arg(expandedPath));
    }
}

void TxFileStream::close() {
    QString expandedPath = ngApp->globalFs()->expandedPath(_inPath);
    if (_inFile == nullptr || !_inFile->isOpen()) {
        throw NgException(QString("Tried to close file that wasn't open: %1")
                              .arg(expandedPath));
    }
    _inFile->close();
}

void TxFileStream::seek(qint64 count) {
    QString expandedPath = ngApp->globalFs()->expandedPath(_inPath);
    if (_inFile == nullptr || !_inFile->isOpen()) {
        throw NgException(QString("Tried to seek file that wasn't open: %1")
                              .arg(expandedPath));
    }
    if (_inFile->seek(_inFile->pos() + count) < 0) {
        throw NgException(
            QString("Couldn't seek in file: %1").arg(expandedPath));
    }
}

qint64 TxFileStream::read(void* buffer, qint64 max) {
    QString expandedPath = ngApp->globalFs()->expandedPath(_inPath);
    if (_inFile == nullptr || !_inFile->isOpen()) {
        throw NgException(QString("Tried to read file that wasn't open: %1")
                              .arg(expandedPath));
    }
    return _inFile->read((char*)buffer, max);
}