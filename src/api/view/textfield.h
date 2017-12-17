#pragma once

#include <QWidget>
#include <QScriptable>
#include <QTextEdit>

namespace api {
namespace view {
class TextField : public QWidget, protected QScriptable {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
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