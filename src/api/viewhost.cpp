#include "viewhost.h"
#include "apihost.h"
#include <api/view/page.h>
#include <api/view/row.h>
#include <api/view/column.h>
#include <api/view/container.h>
#include <api/view/label.h>

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
QScriptValue labelToScriptValue(QScriptEngine *engine,
                                api::view::Label *const &in) {
    return engine->newQObject(in);
}
void labelFromScriptValue(const QScriptValue &object, api::view::Label *&out) {
    out = qobject_cast<api::view::Label *>(object.toQObject());
}

namespace api {
ViewHost::ViewHost(ApiHost *parent) : QObject(parent) {
    QScriptEngine *engine = parent->engine();
    qScriptRegisterMetaType(engine, pageToScriptValue, pageFromScriptValue);
    qScriptRegisterMetaType(engine, rowToScriptValue, rowFromScriptValue);
    qScriptRegisterMetaType(engine, columnToScriptValue, columnFromScriptValue);
    qScriptRegisterMetaType(engine, containerToScriptValue,
                            containerFromScriptValue);
    qScriptRegisterMetaType(engine, labelToScriptValue, labelFromScriptValue);
}
ViewHost::~ViewHost() {}
}  // namespace api