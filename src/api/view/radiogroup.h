#pragma once

#include <QWidget>
#include <QScriptable>
#include <QLabel>
#include <QButtonGroup>
#include <QAbstractButton>
#include <QScriptValue>

namespace api {
namespace view {
class RadioGroup : public QWidget, protected QScriptable {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString selected READ selected WRITE setSelected)
    Q_PROPERTY(QScriptValue onChange READ onChange WRITE setOnChange)
   public:
    explicit RadioGroup(QWidget *parent = 0, bool vertical = false);
    ~RadioGroup();

    QString text() const { return _lbl->text(); }
    void setText(const QString &v) { _lbl->setText(v); }

    QString selected() const;
    void setSelected(const QString &v);

    QScriptValue onChange() const { return _onChange; }
    void setOnChange(const QScriptValue &v) { _onChange = v; }

    Q_INVOKABLE void addOption(const QString &name, const QString &text);

   private slots:
    void buttonGroup_buttonToggled(int id, bool checked);

   private:
    QLabel *_lbl;
    QWidget *_groupWidget;
    QScriptValue _onChange;
    QAbstractButton *_prevButton;
    QButtonGroup *_buttonGroup;
};
}  // namespace view
}  // namespace api