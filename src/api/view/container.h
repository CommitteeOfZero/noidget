#pragma once

#include <QWidget>
#include <QScriptable>
#include <QLayout>
#include "icontainer.h"

namespace api {
namespace view {

class Label;
class TextField;
class CheckBox;

class Container : public QWidget, public IContainer, protected QScriptable {
    Q_OBJECT

   public:
    explicit Container(QWidget* parent = 0);
    virtual ~Container() = 0;

    Q_INVOKABLE api::view::Label* addLabel(const QScriptValue& obj) override;
    Q_INVOKABLE api::view::TextField* addTextField(
        const QScriptValue& obj) override;
    Q_INVOKABLE api::view::CheckBox* addCheckBox(
        const QScriptValue& obj) override;
    Q_INVOKABLE void addRadioGroup() override;
    Q_INVOKABLE void addDirectoryPicker() override;

   protected:
    QLayout* _layout;
};

}  // namespace view
}  // namespace api