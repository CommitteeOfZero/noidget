#pragma once

#include <QObject>
#include <QScriptEngine>

namespace api {

/*^jsdoc
 * @namespace ng
 ^jsdoc*/
class ApiHost : public QObject {
    Q_OBJECT

   public:
    explicit ApiHost(QObject *parent = 0);
    ~ApiHost();
    QScriptEngine *engine() { return _engine; }
    QScriptValue root();

   private:
    QScriptEngine *_engine;
};

}  // namespace api