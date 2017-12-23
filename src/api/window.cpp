#include "installerapplication.h"
#include "installerwindow.h"
#include "window.h"
#include "apihost.h"
#include <api/view/page.h>
#include <view/page.h>
#include <QMessageBox>
#include <api/exception.h>
#include <api/view/dialog.h>
#include <QScriptValue>
#include <QScriptValueList>

namespace api {

Window::Window(ApiHost *parent) : QObject(parent) {}
Window::~Window() {}

api::view::Page *Window::createPage(const QString &title) {
    SCRIPT_EX_GUARD_START
    api::view::Page *page = new api::view::Page(0);
    page->setTitle(title);
    return page;
    SCRIPT_EX_GUARD_END(nullptr)
}

void Window::pushPage(api::view::Page *page) {
    ngApp->window()->push(qobject_cast<::view::Page *>(page));
}

void Window::popPage() { ngApp->window()->pop(); }

void Window::playBgm(const QString &url) {
    // TODO disable this when building without multimedia
    // TODO hide mute button when no BGM set
    ngApp->window()->setBgm(QUrl(url));
}

void Window::messageBox(const QScriptValue &v) {
    QString text;
    bool richText = false;
    if (v.isString()) {
        text = v.toString();
    } else if (v.isObject()) {
        auto text_ = v.property("text");
        if (text_.isString()) {
            text = text_.toString();
            auto richText_ = v.property("richText");
            if (richText_.isBool()) richText = richText_.toBool();
        }
    } else {
        SCRIPT_THROW("Wrong type")
        return;
    }

    QMessageBox mb(ngApp->window());
    mb.setText(text);
    mb.setTextFormat(richText ? Qt::RichText : Qt::PlainText);
    mb.exec();
}

bool Window::modal(const QString &type, const QScriptValue &setup) {
    if (!setup.isFunction()) {
        SCRIPT_THROW("Setup function is required")
        return false;
    }

    api::view::Dialog::DlgType type_;

    if (type == "ok") {
        type_ = api::view::Dialog::DlgType::OK;
    } else {
        SCRIPT_THROW("Unknown dialog type")
        return false;
    }

    api::view::Dialog dlg(type_, ngApp->window());

    // TODO ensure dialog gets deleted in case of exception?
    // (we have nothing that throws here yet)
    SCRIPT_EX_GUARD_START
    QScriptValueList args;
    // script-invokable functions can only take constrefs to QScriptValues
    // so we need to create a new mutable QScriptValue here
    QScriptValue setup_(setup);
    args << setup_.engine()->toScriptValue(&dlg);
    setup_.call(QScriptValue(), args);
    return dlg.present();
    SCRIPT_EX_GUARD_END(false)
}

}  // namespace api
