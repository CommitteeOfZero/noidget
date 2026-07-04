#pragma once

#include <QString>
#include <QJSValue>

namespace api {
namespace view {

class Label;
class Button;
class TextField;
class CheckBox;
class RadioGroup;
class DirectoryPicker;

class Column;
class Row;

class IContainer {
   public:
    virtual ~IContainer() {}
    virtual void addSpace(int space) = 0;
    virtual Label* addLabel(const QJSValue& obj) = 0;
    virtual Button* addButton(const QJSValue& obj) = 0;
    virtual TextField* addTextField(const QJSValue& obj) = 0;
    virtual CheckBox* addCheckBox(const QJSValue& obj) = 0;
    virtual RadioGroup* addRadioGroup(const QJSValue& obj) = 0;
    virtual DirectoryPicker* addDirectoryPicker(const QJSValue& obj) = 0;
    virtual Column* addColumn() = 0;
    virtual Row* addRow() = 0;
};

}  // namespace view
}  // namespace api