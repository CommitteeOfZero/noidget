#include "textfield.h"
#include <QHBoxLayout>

namespace api {
namespace view {

TextField::TextField(QWidget *parent) : QWidget(parent), _richText(false) {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);
    _te = new QTextEdit(this);
    _te->setReadOnly(true);
    _te->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    layout->addWidget(_te);
}
TextField::~TextField() {}

QString TextField::text() const { return _text; }
void TextField::setText(const QString &v) {
    _text = v;
    if (_richText) {
        _te->setHtml(_text);
    } else {
        _te->setPlainText(_text);
    }
}

bool TextField::richText() const { return _richText; }
void TextField::setRichText(bool v) {
    if (v == _richText) return;
    _richText = v;
    if (v) {
        _te->setHtml(_text);
    } else {
        _te->setPlainText(_text);
    }
}

}  // namespace view
}  // namespace api
