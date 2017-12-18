#pragma once

#include <QString>

namespace api {
namespace view {

class Label;
class TextField;
class CheckBox;

class IContainer {
   public:
    virtual ~IContainer() {}
    virtual Label* addLabel(const QScriptValue& obj) = 0;
    virtual TextField* addTextField(const QScriptValue& obj) = 0;
    virtual CheckBox* addCheckBox(const QScriptValue& obj) = 0;
    virtual void addRadioGroup() = 0;
    virtual void addDirectoryPicker() = 0;
};

}  // namespace view
}  // namespace api