#pragma once

#include "txaction.h"
#include <QObject>
#include <QScriptable>

/*^jsdoc
 * Action to write plain text to the log when execution reaches it
 * 
 * Rich text is not supported. Text will be displayed in the UI and written to
 * the plaintext log file.
 * 
 * @class LogAction
 * @extends ng.tx.TxAction
 * @memberof ng.tx
 * @static
 * @toplevel
 * @hideconstructor
 * @property {string} text
 ^jsdoc*/
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