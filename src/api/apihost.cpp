#include <QScriptValue>
#include "apihost.h"
#include "window.h"
#include <api/view/page.h>
#include <api/view/row.h>
#include <api/view/column.h>
#include <api/view/container.h>

namespace api {

// TODO move this crap out
QScriptValue pageToScriptValue(QScriptEngine *engine,
                               api::view::Page *const &in) {
    return engine->newQObject(in);
}
void pageFromScriptValue(const QScriptValue &object, api::view::Page *&out) {
    out = qobject_cast<api::view::Page *>(object.toQObject());
}
QScriptValue rowToScriptValue(QScriptEngine *engine,
                              api::view::Row *const &in) {
    return engine->newQObject(in);
}
void rowFromScriptValue(const QScriptValue &object, api::view::Row *&out) {
    out = qobject_cast<api::view::Row *>(object.toQObject());
}
QScriptValue columnToScriptValue(QScriptEngine *engine,
                                 api::view::Column *const &in) {
    return engine->newQObject(in);
}
void columnFromScriptValue(const QScriptValue &object,
                           api::view::Column *&out) {
    out = qobject_cast<api::view::Column *>(object.toQObject());
}
QScriptValue containerToScriptValue(QScriptEngine *engine,
                                    api::view::Container *const &in) {
    return engine->newQObject(in);
}
void containerFromScriptValue(const QScriptValue &object,
                              api::view::Container *&out) {
    out = qobject_cast<api::view::Container *>(object.toQObject());
}

ApiHost::ApiHost(QObject *parent) : QObject(parent) {
    _engine = new QScriptEngine(this);
    QScriptValue root_ = _engine->newObject();

    qScriptRegisterMetaType(_engine, pageToScriptValue, pageFromScriptValue);
    qScriptRegisterMetaType(_engine, rowToScriptValue, rowFromScriptValue);
    qScriptRegisterMetaType(_engine, columnToScriptValue,
                            columnFromScriptValue);
    qScriptRegisterMetaType(_engine, containerToScriptValue,
                            containerFromScriptValue);

    root_.setProperty("window", _engine->newQObject(new Window(this)));

    _engine->globalObject().setProperty("ng", root_);
}

QScriptValue ApiHost::root() { return _engine->globalObject().property("ng"); }

ApiHost::~ApiHost() {}

}  // namespace api