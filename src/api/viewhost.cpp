#include "viewhost.h"
#include "apihost.h"
#include <api/view/page.h>
#include <api/view/row.h>
#include <api/view/column.h>
#include <api/view/container.h>
#include <api/view/label.h>
#include <api/view/textfield.h>
#include <api/view/checkbox.h>
#include <api/view/radiogroup.h>

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
QScriptValue textFieldToScriptValue(QScriptEngine *engine,
                                    api::view::TextField *const &in) {
    return engine->newQObject(in);
}
void textFieldFromScriptValue(const QScriptValue &object,
                              api::view::TextField *&out) {
    out = qobject_cast<api::view::TextField *>(object.toQObject());
}
QScriptValue checkBoxToScriptValue(QScriptEngine *engine,
                                   api::view::CheckBox *const &in) {
    return engine->newQObject(in);
}
void checkBoxFromScriptValue(const QScriptValue &object,
                             api::view::CheckBox *&out) {
    out = qobject_cast<api::view::CheckBox *>(object.toQObject());
}
QScriptValue radioGroupToScriptValue(QScriptEngine *engine,
                                     api::view::RadioGroup *const &in) {
    return engine->newQObject(in);
}
void radioGroupFromScriptValue(const QScriptValue &object,
                               api::view::RadioGroup *&out) {
    out = qobject_cast<api::view::RadioGroup *>(object.toQObject());
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
    qScriptRegisterMetaType(engine, textFieldToScriptValue,
                            textFieldFromScriptValue);
    qScriptRegisterMetaType(engine, checkBoxToScriptValue,
                            checkBoxFromScriptValue);
    qScriptRegisterMetaType(engine, radioGroupToScriptValue,
                            radioGroupFromScriptValue);
}
ViewHost::~ViewHost() {}
}  // namespace api