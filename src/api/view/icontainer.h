#pragma once

#include <QString>

namespace api {
namespace view {

class Label;
class TextField;
class CheckBox;
class RadioGroup;

class IContainer {
   public:
    virtual ~IContainer() {}
    virtual void addSpace(int space) = 0;
    virtual Label* addLabel(const QScriptValue& obj) = 0;
    virtual TextField* addTextField(const QScriptValue& obj) = 0;
    virtual CheckBox* addCheckBox(const QScriptValue& obj) = 0;
    virtual RadioGroup* addRadioGroup(const QScriptValue& obj) = 0;
    virtual void addDirectoryPicker() = 0;
};

}  // namespace view
}  // namespace api