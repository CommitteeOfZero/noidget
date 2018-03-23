#pragma once

#include "txaction.h"
#include <QObject>
#include <QScriptable>

class LogAction : public TxAction {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)

   public:
    explicit LogAction(QObject* parent = 0) : TxAction(parent) {}
    void run() override;

    QString text() { return _text; }
    void setText(const QString& text) { _text = text; }

   private:
    QString _text;
};