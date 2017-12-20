#include "radiogroup.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <view/flowlayout.h>
#include <QScriptValueList>
#include <QRadioButton>
#include <QScriptContext>

namespace api {
namespace view {

RadioGroup::RadioGroup(QWidget *parent, bool vertical) : QWidget(parent) {
    _lbl = new QLabel(this);
    _lbl->setWordWrap(true);
    _lbl->setTextFormat(Qt::PlainText);

    if (vertical) {
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setMargin(0);
        layout->setSpacing(0);
        layout->setAlignment(Qt::AlignTop);
        setLayout(layout);
        layout->addWidget(_lbl);
        _groupWidget = this;
    } else {
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->setMargin(0);
        layout->setSpacing(0);
        layout->setAlignment(Qt::AlignLeft);
        setLayout(layout);
        layout->addWidget(_lbl, 0, Qt::AlignTop);
        _groupWidget = new QWidget(this);
        FlowLayout *groupLayout = new FlowLayout(_groupWidget, 0, 0, 0);
        _groupWidget->setLayout(groupLayout);
        layout->addWidget(_groupWidget, 1, Qt::AlignTop);
    }

    _buttonGroup = new QButtonGroup(_groupWidget);
    connect(_buttonGroup,
            QOverload<int, bool>::of(&QButtonGroup::buttonToggled), this,
            &RadioGroup::buttonGroup_buttonToggled);
}
RadioGroup::~RadioGroup() {}

QString RadioGroup::selected() const {
    if (_buttonGroup->checkedButton() == nullptr) {
        return "";
    }
    return _buttonGroup->checkedButton()->objectName();
}

void RadioGroup::setSelected(const QString &v) {
    if (v == "") {
        if (_buttonGroup->checkedButton() != nullptr) {
            _buttonGroup->checkedButton()->setChecked(false);
        }
        return;
    }
    QRadioButton *button = _groupWidget->findChild<QRadioButton *>(v);
    if (button != nullptr) {
        button->setChecked(true);
    } else {
        if (context() != nullptr) {
            // TODO proper error type
            context()->throwError("No such button exists");
        }
        return;
    }
}

bool RadioGroup::addOption(const QString &name, const QString &text) {
    if (name == "") {
        if (context() != nullptr) {
            context()->throwError("Empty name not allowed");
        }
        return false;
    }
    QRadioButton *button = _groupWidget->findChild<QRadioButton *>(name);
    if (button != nullptr) {
        if (context() != nullptr) {
            // TODO proper error type
            context()->throwError("Button with this name already exists");
        }
        return false;
    }
    button = new QRadioButton(_groupWidget);
    button->setObjectName(name);
    button->setText(text);
    _buttonGroup->addButton(button);
    _groupWidget->layout()->addWidget(button);
    return true;
}

void RadioGroup::buttonGroup_buttonToggled(int id, bool checked) {
    if (_buttonGroup->checkedButton() == _prevButton) {
        // When user changes selection, buttonToggled gets emitted twice (old
        // option toggled off, new option toggled on), so we need to avoid
        // firing our event twice. checkedButton() is already changed the first
        // time, which makes this possible.
        return;
    }
    _prevButton = _buttonGroup->checkedButton();
    if (_onChange.isFunction()) {
        QScriptValueList args;
        args << selected();
        _onChange.call(QScriptValue(), args);
    }
}

}  // namespace view
}  // namespace api
