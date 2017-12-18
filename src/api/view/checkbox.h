#pragma once

#include <QWidget>
#include <QScriptable>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QMouseEvent>
#include <QScriptValue>

namespace api {
namespace view {
class CheckBox : public QWidget, protected QScriptable {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(bool richText READ richText WRITE setRichText)
    Q_PROPERTY(bool checked READ checked WRITE setChecked)
    Q_PROPERTY(QScriptValue onChange READ onChange WRITE setOnChange)

   public:
    explicit CheckBox(QWidget *parent = 0);
    ~CheckBox();

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

    bool checked() const { return _cb->isChecked(); }
    void setChecked(bool v) { _cb->setChecked(v); }

    QScriptValue onChange() const { return _onChange; }
    void setOnChange(const QScriptValue &v) { _onChange = v; }

   protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

   private slots:
    void qcb_stateChanged(int state);

   private:
    // We need our own label to support rich text and avoid shortcut processing
    QLabel *_lbl;
    QCheckBox *_cb;
    QScriptValue _onChange;
};
}  // namespace view
}  // namespace api