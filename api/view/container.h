#pragma once

#include <QWidget>
#include <QScriptable>
#include <QLayout>
#include "icontainer.h"

namespace api {
namespace view {

class Container : public QWidget, public IContainer, protected QScriptable {
    Q_OBJECT

   public:
    explicit Container(QWidget* parent = 0);
    virtual ~Container() = 0;

    Q_INVOKABLE void addLabel(const QString& v) override;
    Q_INVOKABLE void addTextField() override;
    Q_INVOKABLE void addCheckBox() override;
    Q_INVOKABLE void addRadioGroup() override;
    Q_INVOKABLE void addDirectoryPicker() override;

   protected:
    QLayout* _layout;
};

}  // namespace view
}  // namespace api