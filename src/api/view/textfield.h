#pragma once

#include <QWidget>
#include <QScriptable>
#include <QTextEdit>

namespace api {
namespace view {
/*^jsdoc
* (Read-only) multiline text box with selection, rich text and scrolling
capabilities. Vertical scroll bar is always shown.
* @class TextField
^jsdoc*/
class TextField : public QWidget, protected QScriptable {
    Q_OBJECT
    /*^jsdoc
     * Text, supports wordwrapping
     * @member {string} text
     * @instance
     * @memberof TextField
     ^jsdoc*/
    Q_PROPERTY(QString text READ text WRITE setText)
    /*^jsdoc
     * Render basic HTML?
     *
     * **Default:** `false`
     * @member {boolean} richText
     * @instance
     * @memberof TextField
     ^jsdoc*/
    Q_PROPERTY(bool richText READ richText WRITE setRichText)
   public:
    explicit TextField(QWidget *parent = 0);
    ~TextField();

    QString text() const;
    void setText(const QString &v);

    bool richText() const;
    void setRichText(bool v);

   private:
    QTextEdit *_te;
    QString _text;
    bool _richText;
};
}  // namespace view
}  // namespace api