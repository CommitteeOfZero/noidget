#pragma once

#include "txaction.h"
#include "txstream.h"
#include <QObject>
#include <QScriptable>

class StreamOpenAction : public TxAction {
    Q_OBJECT
    Q_PROPERTY(TxStream* stream READ stream WRITE setStream)

   public:
    explicit StreamOpenAction(QObject* parent = 0) : TxAction(parent) {}
    void run() override;

    TxStream* stream() { return _stream; }
    void setStream(TxStream* const& stream) { _stream = stream; }

   private:
    TxStream* _stream;
};