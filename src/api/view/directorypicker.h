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
class DirectoryPicker : public QWidget, protected QScriptable {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(bool richText READ richText WRITE setRichText)
    Q_PROPERTY(QScriptValue onPick READ onPick WRITE setOnPick)
    Q_PROPERTY(QScriptValue adjustDirectory READ adjustDirectory WRITE
                   setAdjustDirectory)
    Q_PROPERTY(QString value READ value WRITE setValue)
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