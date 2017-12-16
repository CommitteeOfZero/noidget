#pragma once

#include <QWidget>

namespace view {

class IPageStack;

class Page : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)

   public:
    explicit Page(IPageStack *stack, QWidget *parent = 0) : QWidget(parent) {
        _stack = stack;
    }
    virtual ~Page() {}
    virtual void next() = 0;
    virtual void back() = 0;
    virtual QString title() const = 0;

   protected:
    IPageStack *_stack;
   signals:
    void titleChanged(const QString &v);
};

}  // namespace view
