#include "page.h"
#include "column.h"
#include "label.h"
#include "checkbox.h"

namespace api {
namespace view {

Page::Page(QWidget* parent) : ::view::Page(parent) {
    _layout = new QVBoxLayout(this);
    _layout->setMargin(0);
    _layout->setSpacing(8);
    _layout->setAlignment(Qt::AlignTop);
    setLayout(_layout);
    _titleLbl = new QLabel(this);
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

Label* Page::addLabel(const QScriptValue& obj) { return _col->addLabel(obj); }
TextField* Page::addTextField(const QScriptValue& obj) {
    return _col->addTextField(obj);
}
CheckBox* Page::addCheckBox(const QScriptValue& obj) {
    return _col->addCheckBox(obj);
}
void Page::addRadioGroup() { return _col->addRadioGroup(); }
void Page::addDirectoryPicker() { return _col->addDirectoryPicker(); }

}  // namespace view
}  // namespace api
