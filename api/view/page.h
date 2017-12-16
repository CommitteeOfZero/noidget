#pragma once

#include <QScriptable>
#include <QScriptValue>
#include <QVBoxLayout>
#include "view/page.h"
#include "view/ipagestack.h"
#include "api/view/column.h"
#include "api/view/icontainer.h"

namespace api {
namespace view {

class Page : public ::view::Page, public IContainer, protected QScriptable {
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QScriptValue onNext READ onNext WRITE setOnNext)
    Q_PROPERTY(QScriptValue onBack READ onBack WRITE setOnBack)

   public:
    explicit Page(::view::IPageStack* stack, QWidget* parent = 0);
    void next() override;
    void back() override;

    QString title() const override { return _title; }
    void setTitle(const QString& v) { _title = v; }

    QScriptValue onNext() const { return _onNext; }
    void setOnNext(const QScriptValue& v) { _onNext = v; }
    QScriptValue onBack() const { return _onBack; }
    void setOnBack(const QScriptValue& v) { _onBack = v; }

    Q_INVOKABLE void addLabel(const QString& v) override;
    Q_INVOKABLE void addTextField() override;
    Q_INVOKABLE void addCheckBox() override;
    Q_INVOKABLE void addRadioGroup() override;
    Q_INVOKABLE void addDirectoryPicker() override;

   signals:
    void titleChanged(const QString& v);

   private:
    Column* _col;
    QVBoxLayout* _layout;
    QString _title;

    QScriptValue _onNext;
    QScriptValue _onBack;
};

}  // namespace view
}  // namespace api
