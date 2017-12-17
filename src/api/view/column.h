#pragma once

#include <QScriptable>
#include <QVBoxLayout>
#include "container.h"

namespace api {
namespace view {

class Column : public Container {
    Q_OBJECT

   public:
    explicit Column(QWidget *parent = 0) : Container(parent) {
        _layout = new QVBoxLayout(this);
        _layout->setMargin(0);
        _layout->setSpacing(4);  // TODO parameterize
        _layout->setAlignment(Qt::AlignTop);
        setLayout(_layout);
    }
    ~Column() {}
};
}  // namespace view
}  // namespace api