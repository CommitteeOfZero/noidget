#pragma once

#include <QObject>
#include <QScriptable>

class TxStream : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit TxStream() : QObject(0) {}
    virtual ~TxStream() {}
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void seek(qint64 count) = 0;
    virtual qint64 read(void* buffer, qint64 max) = 0;
};