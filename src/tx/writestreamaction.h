#pragma once

#include "txaction.h"
#include "txstream.h"
#include <QObject>
#include <QScriptable>

class WriteStreamAction : public TxAction {
    Q_OBJECT
    Q_PROPERTY(TxStream* stream READ stream WRITE setStream)
    Q_PROPERTY(QString path READ path WRITE setPath)
    Q_PROPERTY(qint64 count READ count WRITE setCount)

   public:
    explicit WriteStreamAction(QObject* parent = 0) : TxAction(parent) {}
    void run() override;

    TxStream* stream() { return _stream; }
    void setStream(TxStream* const& stream) { _stream = stream; }
    QString path() { return _path; }
    void setPath(const QString& path) { _path = path; }
    qint64 count() { return _count; }
    void setCount(qint64 count) { _count = count; }

   private:
    TxStream* _stream;
    QString _path;
    qint64 _count = 0;
    qint64 _progress = 0;

    qint64 calcSize() override { return _count; }
};