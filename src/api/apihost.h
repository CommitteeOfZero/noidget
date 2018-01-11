#pragma once

#include <QObject>
#include <QScriptEngine>
#include <util/exception.h>
#include <QMetaEnum>
#include <api/view/dialog.h>
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

    template <typename T>
    static void registerEnum(QScriptValue &parent);

   private:
    QScriptEngine *_engine;

    template <typename T>
    static QScriptValue enumToScriptValue(QScriptEngine *engine, T const &in);
    template <typename T>
    static void enumFromScriptValue(const QScriptValue &object, T &out);
};

template <typename T>
QScriptValue ApiHost::enumToScriptValue(QScriptEngine *, T const &in) {
    return QScriptValue((int)in);
}
template <typename T>
void ApiHost::enumFromScriptValue(const QScriptValue &object, T &out) {
    out = (T)object.toInt32();
}

template <typename T>
void ApiHost::registerEnum(QScriptValue &parent) {
    if (!parent.isQObject() && !parent.isQMetaObject() && !parent.isObject()) {
        throw NgException(
            "Attempted to register enum on script value that cannot have named "
            "properties");
    }
    auto metaEnum = QMetaEnum::fromType<T>();
    QScriptValue scriptEnum = parent.engine()->newObject();
    for (auto i = 0; i < metaEnum.keyCount(); i++) {
        scriptEnum.setProperty(
            metaEnum.key(i), metaEnum.value(i),
            QScriptValue::ReadOnly | QScriptValue::Undeletable);
    }
    parent.setProperty(metaEnum.name(), scriptEnum,
                       QScriptValue::ReadOnly | QScriptValue::Undeletable);

    qScriptRegisterMetaType(parent.engine(), enumToScriptValue<T>,
                            enumFromScriptValue<T>);
}

}  // namespace api