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
class Button : public QWidget, protected QScriptable {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QScriptValue onClick READ onClick WRITE setOnClick)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled)
    Q_PROPERTY(int width READ width WRITE setWidth)
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