#pragma once

#include <QWidget>
#include <QScriptable>
#include <QHBoxLayout>
#include <QLabel>
#include <QScriptValue>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

namespace api {
namespace view {
/*^jsdoc
 * Text input field with 'browse' button that opens a directory selection dialog
 * @class DirectoryPicker
 * @static
 * @memberof ng.view
 * @hideconstructor
 * @toplevel
 ^jsdoc*/
class DirectoryPicker : public QWidget, protected QScriptable {
    Q_OBJECT
    /*^jsdoc
     * Label text, supports wordwrapping
     * @member {string} text
     * @instance
     * @memberof ng.view.DirectoryPicker
     ^jsdoc*/
    Q_PROPERTY(QString text READ text WRITE setText)
    /*^jsdoc
     * Render basic HTML in label?
     *
     * **Default:** `false`
     * @member {boolean} richText
     * @instance
     * @memberof ng.view.DirectoryPicker
     ^jsdoc*/
    Q_PROPERTY(bool richText READ richText WRITE setRichText)
    /*^jsdoc
     * Custom event handler triggered when a directory is picked using the
     dialog.
     *
     * If this is unset, the result is written straight to the input field. *If
     this is set*, the input field is not changed - the custom handler must do
     so, if appropriate.
     *
     * `function(newDirectory: string)`
     * @member {Function} onPick
     * @instance
     * @memberof ng.view.DirectoryPicker
     ^jsdoc*/
    Q_PROPERTY(QScriptValue onPick READ onPick WRITE setOnPick)
    /*^jsdoc
     * Callback triggered *before* directory selection dialog is opened.
     *
     * This enables changing the directory initially displayed in the dialog. If
     this is unset, the current value of the text field is used. *If this is
     set*, the callback will receive the current text field value, and *must*
     return a path.
     *
     * `function(textFieldValue: string): string`
     * @member {Function} adjustDirectory
     * @instance
     * @memberof ng.view.DirectoryPicker
     ^jsdoc*/
    Q_PROPERTY(QScriptValue adjustDirectory READ adjustDirectory WRITE
                   setAdjustDirectory)
    /*^jsdoc
     * Current text in input field
     * @member {string} value
     * @instance
     * @memberof ng.view.DirectoryPicker
     ^jsdoc*/
    Q_PROPERTY(QString value READ value WRITE setValue)
    /*^jsdoc
    * Window title for directory selection dialog
    * @member {string} title
    * @instance
    * @memberof ng.view.DirectoryPicker
    ^jsdoc*/
    Q_PROPERTY(QString title READ title WRITE setTitle)

   public:
    explicit DirectoryPicker(QWidget *parent = 0);
    ~DirectoryPicker();

    QString text() const { return _lbl->text(); }
    void setText(const QString &v) { _lbl->setText(v); }

    bool richText() const { return _lbl->textFormat() == Qt::RichText; }
    void setRichText(bool v) {
        if (v) {
            _lbl->setTextFormat(Qt::RichText);
        } else {
            _lbl->setTextFormat(Qt::PlainText);
        }
    }

    // NOTE: value not set if onPick exists
    QScriptValue onPick() const { return _onPick; }
    void setOnPick(const QScriptValue &v) { _onPick = v; }

    QScriptValue adjustDirectory() const { return _adjustDirectory; }
    void setAdjustDirectory(const QScriptValue &v) { _adjustDirectory = v; }

    QString value() const { return _edit->text(); }
    void setValue(const QString &v) { _edit->setText(v); }

    QString title() const { return _dlg->windowTitle(); }
    void setTitle(const QString &v) { _dlg->setWindowTitle(v); }

   private slots:
    void dlg_fileSelected(const QString &file);
    void btn_clicked();

   private:
    QLabel *_lbl;
    QLineEdit *_edit;
    QPushButton *_btn;
    QFileDialog *_dlg;
    QScriptValue _onPick;
    QScriptValue _adjustDirectory;
};
}  // namespace view
}  // namespace api