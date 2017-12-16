#pragma once

#include <QScriptable>
#include <QHBoxLayout>
#include "api/view/container.h"

namespace api {
namespace view {

class Row : public Container {
    Q_OBJECT

   public:
    explicit Row(QWidget *parent = 0) : Container(parent) {
        _layout = new QHBoxLayout(this);
        _layout->setMargin(0);
        _layout->setSpacing(4);  // TODO parameterize
        _layout->setAlignment(Qt::AlignLeft);
        setLayout(_layout);
    }
    ~Row() {}
};
}  // namespace view
}  // namespace api