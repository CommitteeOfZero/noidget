#pragma once

#include <QWidget>
#include <QScriptable>
#include <QScriptValue>
#include <QPushButton>

namespace api {
namespace view {
// TODO icons
// TODO remove keyboard shortcut handling
// TODO multiline text
/*^jsdoc
 * Regular old push button.
 * @class Button
 ^jsdoc*/
class Button : public QWidget, protected QScriptable {
    Q_OBJECT
    /*^jsdoc
     * Label. No rich text supported, does not word-wrap.
     * @member {string} text
     * @instance
     * @memberof Button
     ^jsdoc*/
    Q_PROPERTY(QString text READ text WRITE setText)
    /*^jsdoc
     * Click event handler.
     *
     * `function()`
     * @member {Function} onClick
     * @instance
     * @memberof Button
    ^jsdoc*/
    Q_PROPERTY(QScriptValue onClick READ onClick WRITE setOnClick)
    /*^jsdoc
     * Is button clickable?
     *
     * **Default:** `true`
     * @member {boolean} enabled
     * @instance
     * @memberof Button
     ^jsdoc*/
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled)
    /*^jsdoc
     * Fixed button width. **TODO** stretching behaviour when unset
     * @member {number} width
     * @instance
     * @memberof Button
     ^jsdoc*/
    Q_PROPERTY(int width READ width WRITE setWidth)
    /*^jsdoc
     * Fixed button height. **TODO** stretching behaviour when unset
     * @member {number} height
     * @instance
     * @memberof Button
     ^jsdoc*/
    Q_PROPERTY(int height READ height WRITE setHeight)
   public:
    explicit Button(QWidget *parent = 0);
    ~Button();

    QString text() const { return _btn->text(); }
    void setText(const QString &v) { _btn->setText(v); }

    QScriptValue onClick() const { return _onClick; }
    void setOnClick(const QScriptValue &v) { _onClick = v; }

    bool enabled() const { return _btn->isEnabled(); }
    void setEnabled(bool v) { _btn->setEnabled(v); }

    int width() const { return _btn->width(); }
    void setWidth(int v) { _btn->setFixedWidth(v); }
    int height() const { return _btn->height(); }
    void setHeight(int v) { _btn->setFixedHeight(v); }

   private slots:
    void btn_clicked();

   private:
    QPushButton *_btn;
    QScriptValue _onClick;
};
}  // namespace view
}  // namespace api