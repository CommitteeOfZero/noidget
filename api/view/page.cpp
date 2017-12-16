#include "api/view/page.h"

namespace api {
namespace view {

Page::Page(::view::IPageStack* stack, QWidget* parent)
    : ::view::Page(stack, parent) {
    _layout = new QVBoxLayout(this);
    _layout->setMargin(0);
    _layout->setSpacing(0);
    setLayout(_layout);
    _col = new Column(this);
    _layout->addWidget(_col);
}

void Page::next() {}
void Page::back() {}

void Page::addLabel(const QString& v) { return _col->addLabel(v); }
void Page::addTextField() { return _col->addTextField(); }
void Page::addCheckBox() { return _col->addCheckBox(); }
void Page::addRadioGroup() { return _col->addRadioGroup(); }
void Page::addDirectoryPicker() { return _col->addDirectoryPicker(); }

}  // namespace view
}  // namespace api
