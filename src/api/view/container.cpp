#include "container.h"
#include "label.h"
#include "textfield.h"
#include "checkbox.h"
#include "radiogroup.h"
#include <QScriptValue>
#include <QScriptContext>
#include <util/exception.h>

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
RadioGroup* Container::addRadioGroup(const QScriptValue& obj) {
    if (!obj.isObject()) {
        if (context() == nullptr) {
            throw NgException("Wrong type");
        } else {
            // TODO proper error type
            context()->throwError("Wrong type");
        }
        return nullptr;
    }

    bool vertical = false;
    auto vertical_ = obj.property("vertical");
    if (vertical_.isBool()) vertical = vertical_.toBool();

    RadioGroup* grp = new RadioGroup(this, vertical);

    auto text_ = obj.property("text");
    if (text_.isString()) rg->setText(text_.toString());

    auto options_ = obj.property("options");
    if (options_.isArray()) {
        QScriptValueIterator it(options_);
        while (it.hasNext()) {
            it.next();
            auto option = it.value();
            if (option.isObject()) {
                QString oName;
                QString oText;
                auto oName_ = option.property("name");
                if (oName_.isString()) oName = oName_.toString();
                auto oText_ = option.property("text");
                if (oText_.isString()) oText = oText_.toString();

                try {
                    grp->nativeAddOption(oName, oText);
                } catch (const NgException& ex) {
                    delete grp;
                    if (context() == nullptr) {
                        throw NgException("Invalid option for RadioGroup");
                    } else {
                        context()->throwError("Invalid option for RadioGroup");
                    }
                    return nullptr;
                }
            }
        }
    }

    grp->setOnChange(obj.property("onChange"));

    auto preset_ = obj.property("preset");
    if (preset_.isString()) {
        try {
            grp->nativeSetSelected(preset_.toString());
        } catch (const NgException& ex) {
            delete grp;
            if (context() == nullptr) {
                throw NgException("Invalid preset for RadioGroup");
            } else {
                context()->throwError("Invalid preset for RadioGroup");
            }
            return nullptr;
        }
    }

    _layout->addWidget(grp);
    return grp;
}
void Container::addDirectoryPicker() {}

}  // namespace view
}  // namespace api