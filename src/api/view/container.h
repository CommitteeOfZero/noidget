#pragma once

#include <QWidget>
#include <QBoxLayout>
#include "icontainer.h"

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

/*^jsdoc
 * Abstract base class for widgets containing child widgets
 * @class Container
 * @memberof ng.view
 * @static
 * @toplevel
 * @hideconstructor
 ^jsdoc*/
class Container : public QWidget, public IContainer {
    Q_OBJECT

   public:
    explicit Container(QWidget* parent = 0);
    virtual ~Container() = 0;

    Q_INVOKABLE void addSpace(int space) override;

    Q_INVOKABLE api::view::Label* addLabel(const QJSValue& obj) override;
    Q_INVOKABLE api::view::Button* addButton(const QJSValue& obj) override;
    Q_INVOKABLE api::view::TextField* addTextField(
        const QJSValue& obj) override;
    Q_INVOKABLE api::view::CheckBox* addCheckBox(
        const QJSValue& obj) override;
    Q_INVOKABLE api::view::RadioGroup* addRadioGroup(
        const QJSValue& obj) override;
    Q_INVOKABLE api::view::DirectoryPicker* addDirectoryPicker(
        const QJSValue& obj) override;

    Q_INVOKABLE api::view::Column* addColumn() override;
    Q_INVOKABLE api::view::Row* addRow() override;

   protected:
    QBoxLayout* _layout;
};

}  // namespace view
}  // namespace api