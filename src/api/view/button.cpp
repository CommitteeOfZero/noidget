#include "button.h"
#include <QVBoxLayout>
#include <api/exception.h>

namespace api {
namespace view {

Button::Button(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);
    _btn = new QPushButton(this);
    layout->addWidget(_btn);
    connect(_btn, &QPushButton::clicked, this, &Button::btn_clicked);
}
Button::~Button() {}

void Button::btn_clicked() {
    if (_onClick.isCallable()) {
        reportIfScriptError(_onClick.call());
    }
}

}  // namespace view
}  // namespace api
