#include "receipt.h"
#include "installerapplication.h"
#include "fs.h"
#include "util/exception.h"
#include <QFileInfo>

// NOTE: QIODevice::Unbuffered is not supported on Windows, hence we still need to flush() manually

void Receipt::open(const QString& dir) {
    if (_outFile != nullptr) {
        throw NgException("Tried to open receipt twice");
    }

    _isLogging = true;
    ngApp->globalFs()->createDirectory(dir);
    QString filePath = ngApp->globalFs()->expandedPath(dir + "/ngreceipt.bin");
    if (ngApp->globalFs()->pathExists(filePath)) {
        Store oldStore;
        try {
            oldStore = loadOldLog(filePath);
        } catch (const NgException& ex) {
            _isLogging = false;
            throw;
        }
        QSet<QString> newFiles;
        newFiles = _store.filesCreated;
        newFiles.subtract(oldStore.filesCreated);
        _outFile = new QFile(filePath, this);
        if (!_outFile->open(QIODevice::ReadWrite | QIODevice::Append |
                            QIODevice::Unbuffered)) {
            _isLogging = false;
            delete _outFile;
            _outFile = nullptr;
            throw NgException(
                QString("Couldn't write to receipt at %1").arg(filePath));
        }
        // TODO handle version upgrades?
        _out.setDevice(_outFile);
        _out.setVersion(QDataStream::Qt_5_9);
        for (const QString& f : newFiles) {
            _out << (int)TokenType::File;
            _out << f;
        }
        _outFile->flush();
    } else {
        _outFile = new QFile(filePath, this);
        if (!_outFile->open(QIODevice::WriteOnly | QIODevice::Unbuffered)) {
            _isLogging = false;
            delete _outFile;
            _outFile = nullptr;
            throw NgException(
                QString("Couldn't create receipt at %1").arg(filePath));
        }
        _out.setDevice(_outFile);
        _out.setVersion(QDataStream::Qt_5_9);
        _out << FileFormatVersion;
        for (const QString& f : _store.filesCreated) {
            _out << (int)TokenType::File;
            _out << f;
        }
        _outFile->flush();
        logFileCreate(filePath);
    }
}

void Receipt::close() {
    if (_outFile == nullptr | !_outFile->isOpen()) {
        throw NgException("Tried to close receipt that wasn't open");
    }
    _outFile->close();
    delete _outFile;
    _outFile = nullptr;
    _isLogging = false;
}

void Receipt::logFileCreate(const QString& path) {
    if (!_isLogging) return;
    auto expandedPath =
        QFileInfo(ngApp->globalFs()->expandedPath(path)).canonicalFilePath();
    if (!_store.filesCreated.contains(expandedPath)) {
        _store.filesCreated << expandedPath;
        if (_outFile != nullptr && _outFile->isOpen()) {
            _out << (int)TokenType::File;
            _out << expandedPath;
            _outFile->flush();
        }
    }
}

Receipt::Store Receipt::loadOldLog(const QString& path) {
    QFile inFile(path);
    if (!inFile.open(QIODevice::ReadOnly)) {
        throw NgException(QString("Couldn't open receipt at %1").arg(path));
    }
    Store result;
    QDataStream in(&inFile);
    in.setVersion(QDataStream::Qt_5_9);
    in >> result.version;
    while (!in.atEnd()) {
        TokenType type;
        in >> (qint32&)type;
        switch (type) {
            case TokenType::File: {
                QString createdFile;
                in >> createdFile;
                result.filesCreated << createdFile;
            }
        }
    }
    return result;
}