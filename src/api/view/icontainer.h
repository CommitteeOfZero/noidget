#pragma once

#include <QString>

namespace api {
namespace view {

class Label;

class IContainer {
   public:
    virtual ~IContainer() {}
    virtual Label* addLabel(const QScriptValue& obj) = 0;
    virtual void addTextField() = 0;
    virtual void addCheckBox() = 0;
    virtual void addRadioGroup() = 0;
    virtual void addDirectoryPicker() = 0;
};

}  // namespace view
}  // namespace api