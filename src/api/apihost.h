#pragma once

#include <QObject>
#include <QJSEngine>
#include <util/exception.h>
#include <QMetaEnum>
#include <api/view/dialog.h>
namespace api {

/*^jsdoc
 * ## How to read this
 *
 * - Symbols without parentheses indicate static ("namespace") objects.
 * - Class parameters (in parentheses) are instance properties set at
 construction time which cannot be changed (and maybe not even read) later on.
 * - Simple instance members are often listed in a "properties" table for
 brevity - these are equivalent to "instance members".
 * - Unless otherwise noted (with a visible constructor), classes are
 instantiated through factory methods. Refer to the class properties/instance
 data members for descriptions of the factory methods' parameters.
 * - Some classes/functions have event handler/callback instance
 members/parameters. The signatures for these are given in their descriptions.
 *
 * @namespace ng
 * @toplevel
 ^jsdoc*/
class ApiHost : public QObject {
    Q_OBJECT

   public:
    explicit ApiHost(QObject *parent = 0);
    ~ApiHost();
    QJSEngine *engine() { return _engine; }
    QJSValue root();

    template <typename T>
    static void registerEnum(QJSEngine *engine, QJSValue &parent);

   private:
    QJSEngine *_engine;
};

template <typename T>
void ApiHost::registerEnum(QJSEngine *engine, QJSValue &parent) {
    if (!parent.isQObject() && !parent.isQMetaObject() && !parent.isObject()) {
        throw NgException(
            "Attempted to register enum on script value that cannot have named "
            "properties");
    }
    auto metaEnum = QMetaEnum::fromType<T>();
    QJSValue scriptEnum = engine->newObject();
    for (auto i = 0; i < metaEnum.keyCount(); i++) {
        scriptEnum.setProperty(metaEnum.key(i), metaEnum.value(i));
    }
    parent.setProperty(metaEnum.name(), scriptEnum);
}

}  // namespace api
