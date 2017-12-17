#include "installerapplication.h"
#include "installerwindow.h"
#include "window.h"
#include "apihost.h"
#include <api/view/page.h>
#include <view/page.h>
#include <QMessageBox>

namespace api {

Window::Window(ApiHost *parent) : QObject(parent) {}
Window::~Window() {}

api::view::Page *Window::createPage(const QString &title) {
    api::view::Page *page = new api::view::Page(0);
    page->setTitle(title);
    return page;
}

void Window::pushPage(api::view::Page *page) {
    ngApp->window()->push(qobject_cast<::view::Page *>(page));
}

void Window::popPage() { ngApp->window()->pop(); }

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
        if (context() != 0) {
            // TODO proper error type
            context()->throwError("Wrong type");
        }
        return;
    }

    QMessageBox mb(ngApp->window());
    mb.setText(text);
    mb.setTextFormat(richText ? Qt::RichText : Qt::PlainText);
    mb.exec();
}

}  // namespace api
