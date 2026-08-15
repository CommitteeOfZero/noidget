#pragma once

#include <QJSValue>
#include <QVBoxLayout>
#include <QLabel>
#include <view/page.h>
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
 * Wizard page. Uses {@link ng.view.Column} to contain child widgets.
 * @class Page
 * @extends ng.view.Container
 * @static
 * @memberof ng.view
 * @toplevel
 * @hideconstructor
 * @property {string} title - Page title, displayed on the page, **not** the
 window title. Rich text is not allowed.
 ^jsdoc*/
class Page : public ::view::Page, public IContainer {
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    /*^jsdoc
     * Event handler called when the page's "next" button is clicked. Natively,
     * this click does nothing - page controllers must implement any applicable
     * page changing logic.
     *
     * `function()`
     * @member {Function} onNext
     * @instance
     * @memberof ng.view.Page
     ^jsdoc*/
    Q_PROPERTY(QJSValue onNext READ onNext WRITE setOnNext)
    /*^jsdoc
     * Event handler called when the page's "back" button is clicked. Unlike
     * {@link Page#onNext}, the current page will be destroyed after this is
     * called, or if there's no handler set.
     *
     * `function()`
     * @member {Function} onBack
     * @instance
     * @memberof ng.view.Page
    ^jsdoc*/
    Q_PROPERTY(QJSValue onBack READ onBack WRITE setOnBack)

   public:
    explicit Page(QWidget* parent = 0);
    void next() override;
    void back() override;
    void attached() override;

    QString title() const override { return _titleLbl->text(); }
    void setTitle(const QString& v) {
        _titleLbl->setText(v);
        emit titleChanged(v);
    }

    QJSValue onNext() const { return _onNext; }
    void setOnNext(const QJSValue& v) { _onNext = v; }
    QJSValue onBack() const { return _onBack; }
    void setOnBack(const QJSValue& v) { _onBack = v; }

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

   signals:
    void titleChanged(const QString& v);

   private:
    Column* _col;
    QVBoxLayout* _layout;
    QLabel* _titleLbl;

    QJSValue _onNext;
    QJSValue _onBack;
};

}  // namespace view
}  // namespace api
