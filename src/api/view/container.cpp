#include "container.h"
#include "label.h"
#include "textfield.h"
#include "checkbox.h"
#include "radiogroup.h"
#include "column.h"
#include "row.h"
#include <QScriptValue>
#include <QScriptValueIterator>
#include <api/exception.h>

namespace api {
namespace view {

Container::Container(QWidget* parent) : QWidget(parent) {}
Container::~Container() {}

// TODO do this without QBoxLayout::addSpacing, to support FlowLayouts
void Container::addSpace(int space) { _layout->addSpacing(space); }

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
        SCRIPT_THROW("Wrong type")
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
        SCRIPT_THROW("Wrong type")
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
        SCRIPT_THROW("Wrong type")
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
        SCRIPT_THROW("Wrong type")
        return nullptr;
    }

    bool vertical = false;
    auto vertical_ = obj.property("vertical");
    if (vertical_.isBool()) vertical = vertical_.toBool();

    RadioGroup* grp = new RadioGroup(this, vertical);

    auto text_ = obj.property("text");
    if (text_.isString()) grp->setText(text_.toString());

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
                    grp->addOption(oName, oText);
                } catch (const NgException& ex) {
                    delete grp;
                    SCRIPT_THROW("Invalid option for RadioGroup")
                    return nullptr;
                }
            }
        }
    }

    grp->setOnChange(obj.property("onChange"));

    auto preset_ = obj.property("preset");
    if (preset_.isString()) {
        try {
            grp->setSelected(preset_.toString());
        } catch (const NgException& ex) {
            delete grp;
            SCRIPT_THROW("Invalid option for RadioGroup")
            return nullptr;
        }
    }

    _layout->addWidget(grp);
    return grp;
}
void Container::addDirectoryPicker() {}

Column* Container::addColumn() {
    SCRIPT_EX_GUARD_START
    Column* col = new Column(this);
    _layout->addWidget(col);
    return col;
    SCRIPT_EX_GUARD_END(nullptr)
}
Row* Container::addRow() {
    SCRIPT_EX_GUARD_START
    Row* row = new Row(this);
    _layout->addWidget(row);
    return row;
    SCRIPT_EX_GUARD_END(nullptr)
}

}  // namespace view
}  // namespace api