#pragma once

#include <QScriptable>
#include <QScriptValue>
#include <QVBoxLayout>
#include <QLabel>
#include <view/page.h>
#include "icontainer.h"

namespace api {
namespace view {

class Column;
class Label;

class Page : public ::view::Page, public IContainer, protected QScriptable {
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QScriptValue onNext READ onNext WRITE setOnNext)
    Q_PROPERTY(QScriptValue onBack READ onBack WRITE setOnBack)

   public:
    explicit Page(QWidget* parent = 0);
    void next() override;
    void back() override;

    QString title() const override { return _titleLbl->text(); }
    void setTitle(const QString& v) { _titleLbl->setText(v); }

    QScriptValue onNext() const { return _onNext; }
    void setOnNext(const QScriptValue& v) { _onNext = v; }
    QScriptValue onBack() const { return _onBack; }
    void setOnBack(const QScriptValue& v) { _onBack = v; }

    Q_INVOKABLE api::view::Label* addLabel(const QScriptValue& obj) override;
    Q_INVOKABLE api::view::TextField* addTextField(
        const QScriptValue& obj) override;
    Q_INVOKABLE void addCheckBox() override;
    Q_INVOKABLE void addRadioGroup() override;
    Q_INVOKABLE void addDirectoryPicker() override;

   signals:
    void titleChanged(const QString& v);

   private:
    Column* _col;
    QVBoxLayout* _layout;
    QLabel* _titleLbl;

    QScriptValue _onNext;
    QScriptValue _onBack;
};

}  // namespace view
}  // namespace api
