#pragma once

#include "txstream.h"
#include <QObject>
#include <QFile>

class TxFileStream : public TxStream {
    Q_OBJECT
    Q_PROPERTY(QString inPath READ inPath WRITE setInPath)

   public:
    explicit TxFileStream() : TxStream() {}
    ~TxFileStream() {}
    void open() override;
    void close() override;
    void seek(qint64 count) override;
    qint64 read(void* buffer, qint64 max) override;

    QString inPath() { return _inPath; }
    void setInPath(const QString& inPath) { _inPath = inPath; }

   private:
    QString _inPath;
    QFile* _inFile = 0;
};