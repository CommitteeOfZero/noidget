#include "container.h"
#include <QLabel>

namespace api {
namespace view {

Container::Container(QWidget* parent) : QWidget(parent) {}
Container::~Container() {}

void Container::addLabel(const QString& v) {
    QLabel* lbl = new QLabel(this);
    lbl->setText(v);
    _layout->addWidget(lbl);
}
void Container::addTextField() {}
void Container::addCheckBox() {}
void Container::addRadioGroup() {}
void Container::addDirectoryPicker() {}

}  // namespace view
}  // namespace api