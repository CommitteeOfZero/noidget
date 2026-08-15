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

namespace api {
ViewHost::ViewHost(ApiHost *parent) : QObject(parent) {
    qRegisterMetaType<api::view::Page *>("Page*");
    qRegisterMetaType<api::view::Row *>("Row*");
    qRegisterMetaType<api::view::Column *>("Column*");
    qRegisterMetaType<api::view::Container *>("Container*");
    qRegisterMetaType<api::view::Label *>("Label*");
    qRegisterMetaType<api::view::TextField *>("TextField*");
    qRegisterMetaType<api::view::CheckBox *>("CheckBox*");
    qRegisterMetaType<api::view::RadioGroup *>("RadioGroup*");
    qRegisterMetaType<api::view::DirectoryPicker *>("DirectoryPicker*");
    qRegisterMetaType<api::view::Dialog *>("Dialog*");
    qRegisterMetaType<api::view::Button *>("Button*");
}
void ViewHost::setupScriptObject(QJSValue &o) {
    ApiHost::registerEnum<api::view::Dialog::DlgType>(qjsEngine(this), o);
}
ViewHost::~ViewHost() {}
}  // namespace api
