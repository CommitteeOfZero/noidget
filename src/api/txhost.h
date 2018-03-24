#pragma once

#include <QObject>
#include <QScriptable>
#include <QScriptValue>

class Transaction;

namespace api {

class ApiHost;

/*^jsdoc
 * @namespace tx
 * @memberof ng
 * @static
 * @toplevel
 ^jsdoc*/
class TxHost : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit TxHost(ApiHost* parent);
    void setupScriptObject(QScriptValue& o);
    ~TxHost();

    Q_INVOKABLE Transaction* tx();
    Q_INVOKABLE void run();
};
}  // namespace api