#include "page.h"
#include "column.h"
#include "label.h"
#include "checkbox.h"
#include "radiogroup.h"
#include <api/exception.h>

namespace api {
namespace view {

Page::Page(QWidget* parent) : ::view::Page(parent) {
    _layout = new QVBoxLayout(this);
    _layout->setMargin(0);
    _layout->setSpacing(8);
    _layout->setAlignment(Qt::AlignTop);
    setLayout(_layout);
    _titleLbl = new QLabel(this);
    _titleLbl->setTextFormat(Qt::PlainText);
    _titleLbl->setWordWrap(true);
    _titleLbl->setStyleSheet("font-weight: bold");
    _layout->addWidget(_titleLbl);
    _col = new Column(this);
    _layout->addWidget(_col);
}

void Page::next() {
    if (_onNext.isFunction()) {
        _onNext.call();
    }
}
void Page::back() {
    if (_onBack.isFunction()) {
        _onBack.call();
    }
    // TODO check allowed by script
    emit popRequested();
}

void Page::addSpace(int space) { _col->addSpace(space); }

Label* Page::addLabel(const QScriptValue& obj) {
    SCRIPT_EX_GUARD_START
    return _col->addLabel(obj);
    SCRIPT_EX_GUARD_END(nullptr)
}
TextField* Page::addTextField(const QScriptValue& obj) {
    SCRIPT_EX_GUARD_START
    return _col->addTextField(obj);
    SCRIPT_EX_GUARD_END(nullptr)
}
CheckBox* Page::addCheckBox(const QScriptValue& obj) {
    SCRIPT_EX_GUARD_START
    return _col->addCheckBox(obj);
    SCRIPT_EX_GUARD_END(nullptr)
}
RadioGroup* Page::addRadioGroup(const QScriptValue& obj) {
    SCRIPT_EX_GUARD_START
    return _col->addRadioGroup(obj);
    SCRIPT_EX_GUARD_END(nullptr)
}
void Page::addDirectoryPicker() { return _col->addDirectoryPicker(); }

}  // namespace view
}  // namespace api
