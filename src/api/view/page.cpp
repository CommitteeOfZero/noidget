#include "page.h"
#include "column.h"
#include "label.h"

namespace api {
namespace view {

Page::Page(QWidget* parent) : ::view::Page(parent) {
    _layout = new QVBoxLayout(this);
    _layout->setMargin(0);
    _layout->setSpacing(8);
    setLayout(_layout);
    _titleLbl = new QLabel(this);
    _layout->addWidget(_titleLbl);
    _col = new Column(this);
    _layout->addWidget(_col);
    _layout->addStretch();  // TODO is this good?
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
void Page::addTextField() { return _col->addTextField(); }
void Page::addCheckBox() { return _col->addCheckBox(); }
void Page::addRadioGroup() { return _col->addRadioGroup(); }
void Page::addDirectoryPicker() { return _col->addDirectoryPicker(); }

}  // namespace view
}  // namespace api
