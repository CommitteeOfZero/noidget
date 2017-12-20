#include "installerapplication.h"
#include "installerwindow.h"
#include "window.h"
#include "apihost.h"
#include <api/view/page.h>
#include <view/page.h>
#include <QMessageBox>
#include <api/exception.h>

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

}  // namespace api
