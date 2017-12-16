#include "api/view/container.h"

namespace api {
namespace view {

Container::Container(QWidget* parent) : QWidget(parent) {}
Container::~Container() {}

void Container::addLabel(const QString& v) {}
void Container::addTextField() {}
void Container::addCheckBox() {}
void Container::addRadioGroup() {}
void Container::addDirectoryPicker() {}

}  // namespace view
}  // namespace api