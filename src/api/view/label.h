#pragma once

#include <QWidget>
#include <QScriptable>
#include <QLabel>

namespace api {
namespace view {
class Label : public QWidget, protected QScriptable {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(bool richText READ richText WRITE setRichText)
   public:
    explicit Label(QWidget *parent = 0);
    ~Label();

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

   private:
    QLabel *_lbl;
};
}  // namespace view
}  // namespace api