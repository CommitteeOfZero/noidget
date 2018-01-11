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
#include <api/view/directorypicker.h>
#include <api/view/dialog.h>
#include <api/view/button.h>
#include <QMetaEnum>
#include <QDebug>

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
QScriptValue directoryPickerToScriptValue(
    QScriptEngine *engine, api::view::DirectoryPicker *const &in) {
    return engine->newQObject(in);
}
void directoryPickerFromScriptValue(const QScriptValue &object,
                                    api::view::DirectoryPicker *&out) {
    out = qobject_cast<api::view::DirectoryPicker *>(object.toQObject());
}
QScriptValue dialogToScriptValue(QScriptEngine *engine,
                                 api::view::Dialog *const &in) {
    return engine->newQObject(in);
}
void dialogFromScriptValue(const QScriptValue &object,
                           api::view::Dialog *&out) {
    out = qobject_cast<api::view::Dialog *>(object.toQObject());
}
QScriptValue buttonToScriptValue(QScriptEngine *engine,
                                 api::view::Button *const &in) {
    return engine->newQObject(in);
}
void buttonFromScriptValue(const QScriptValue &object,
                           api::view::Button *&out) {
    out = qobject_cast<api::view::Button *>(object.toQObject());
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
    qScriptRegisterMetaType(engine, directoryPickerToScriptValue,
                            directoryPickerFromScriptValue);
    qScriptRegisterMetaType(engine, dialogToScriptValue, dialogFromScriptValue);
    qScriptRegisterMetaType(engine, buttonToScriptValue, buttonFromScriptValue);
}
void ViewHost::setupScriptObject(QScriptValue &o) {
    ApiHost::registerEnum<api::view::Dialog::DlgType>(o);
}
ViewHost::~ViewHost() {}
}  // namespace api