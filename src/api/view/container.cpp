#include "container.h"
#include "label.h"
#include "textfield.h"
#include "checkbox.h"
#include <QScriptValue>
#include <QScriptContext>

namespace api {
namespace view {

Container::Container(QWidget* parent) : QWidget(parent) {}
Container::~Container() {}

Label* Container::addLabel(const QScriptValue& obj) {
    QString text;
    bool richText = false;

    if (obj.isString()) {
        text = obj.toString();
    } else if (obj.isObject()) {
        auto text_ = obj.property("text");
        if (text_.isString()) text = text_.toString();
        auto richText_ = obj.property("richText");
        if (richText_.isBool()) richText = richText_.toBool();
    } else {
        if (context() != 0) {
            // TODO proper error type
            context()->throwError("Wrong type");
        }
        return nullptr;
    }

    Label* lbl = new Label(this);
    lbl->setText(text);
    lbl->setRichText(richText);
    _layout->addWidget(lbl);
    return lbl;
}
TextField* Container::addTextField(const QScriptValue& obj) {
    QString text;
    bool richText = false;

    if (obj.isString()) {
        text = obj.toString();
    } else if (obj.isObject()) {
        auto text_ = obj.property("text");
        if (text_.isString()) text = text_.toString();
        auto richText_ = obj.property("richText");
        if (richText_.isBool()) richText = richText_.toBool();
    } else {
        if (context() != 0) {
            // TODO proper error type
            context()->throwError("Wrong type");
        }
        return nullptr;
    }

    TextField* tf = new TextField(this);
    tf->setText(text);
    tf->setRichText(richText);
    _layout->addWidget(tf);
    return tf;
}
CheckBox* Container::addCheckBox(const QScriptValue& obj) {
    QString text;
    bool richText = false;
    bool preset = false;
    QScriptValue onChange(QScriptValue::UndefinedValue);

    if (obj.isString()) {
        text = obj.toString();
    } else if (obj.isObject()) {
        auto text_ = obj.property("text");
        if (text_.isString()) text = text_.toString();
        auto richText_ = obj.property("richText");
        if (richText_.isBool()) richText = richText_.toBool();
        // important: set this *before* onChange, so the handler isn't called
        // for default setup
        auto preset_ = obj.property("preset");
        if (preset_.isBool()) preset = preset_.toBool();
        onChange = obj.property("onChange");
    } else {
        if (context() != 0) {
            // TODO proper error type
            context()->throwError("Wrong type");
        }
        return nullptr;
    }

    CheckBox* cb = new CheckBox(this);
    cb->setText(text);
    cb->setRichText(richText);
    cb->setChecked(preset);
    cb->setOnChange(onChange);
    _layout->addWidget(cb);
    return cb;
}
void Container::addRadioGroup() {}
void Container::addDirectoryPicker() {}

}  // namespace view
}  // namespace api