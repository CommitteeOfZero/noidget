#include "installerapplication.h"
#include "installerwindow.h"
#include "window.h"
#include <api/view/page.h>
#include <view/page.h>
#include <QMessageBox>

namespace api {

Window::Window(QObject *parent) : QObject(parent) {}
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

void Window::messageBox(const QString &message) {
    // TODO rich text?
    QMessageBox mb(ngApp->window());
    mb.setText(message);
    mb.exec();
}

}  // namespace api
