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

Window::Window(ApiHost *parent) : QObject(parent), _mbIcon() {}
Window::~Window() {}

/*^jsdoc
 * Creates a new blank page. The page is not yet added to the wizard stack and
 thus not displayed and receives no events.
 * @method createPage
 * @memberof ng.window
 * @static
 * @param {string} title
 * @returns {ng.view.Page}
 ^jsdoc*/
api::view::Page *Window::createPage(const QString &title) {
    SCRIPT_EX_GUARD_START
    api::view::Page *page = new api::view::Page(0);
    page->setTitle(title);
    return page;
    SCRIPT_EX_GUARD_END(nullptr)
}

/*^jsdoc
 * Displays `page` in the wizard. The previous page remains loaded but receives
 no button press events.
 * @method pushPage
 * @memberof ng.window
 * @static
 * @param {ng.view.Page} page
 ^jsdoc*/
void Window::pushPage(api::view::Page *page) {
    ngApp->window()->push(qobject_cast<::view::Page *>(page));
}

/*^jsdoc
 * Goes back to the previous wizard page. The current page is deleted.
 * @method popPage
 * @memberof ng.window
 * @static
 ^jsdoc*/
void Window::popPage() { ngApp->window()->pop(); }

/*^jsdoc
 * Starts playing a new BGM track.
 * 
 * **When using a BGM track from resources**, `url` must be prefixed with `qrc:/`, not just `:/` like usual.
 * 
 * @method playBgm
 * @memberof ng.window
 * @static
 * @param {string} url
 ^jsdoc*/
void Window::playBgm(const QString &url) {
    // TODO disable this when building without multimedia
    // TODO hide mute button when no BGM set
    ngApp->window()->setBgm(QUrl(url));
}

/*^jsdoc
 * Displays a message box. Returns only after user closes the box.
 * @method messageBox
 * @memberof ng.window
 * @static
 * @param {string} text - plain text
 ^jsdoc*/
/*^jsdoc
 * Displays a message box. Returns only after user closes the box.
 * @method messageBox
 * @memberof ng.window
 * @static
 * @param {object} params
 * @param {string} params.text
 * @param {boolean} [params.richText=false]
 ^jsdoc*/
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
    if (!_mbIcon.isNull()) {
        mb.setIconPixmap(_mbIcon);
    }
    mb.exec();
}

/*^jsdoc
 * Load an icon to be used for all message boxes.
 * @method setMessageBoxIcon
 * @memberof ng.window
 * @static
 * @param {string} url
 ^jsdoc*/
void Window::setMessageBoxIcon(const QString &url) { _mbIcon = QPixmap(url); }

/*^jsdoc
 * Displays a customized modal {@link ng.view.Dialog}. Returns only after user
 closes the dialog.
 * @method modal
 * @memberof ng.window
 * @static
 * @param {ng.view.DlgType} type
 * @param {Function} setup
 * Called with newly created to set up child widgets etc. before display.
 *
 * `function(dialog: ng.view.Dialog) {}`
 * @returns {boolean} - was the dialog accepted or rejected? (`OK` type dialogs
 always return true)
 ^jsdoc*/
bool Window::modal(api::view::Dialog::DlgType type, const QScriptValue &setup) {
    if (!setup.isFunction()) {
        SCRIPT_THROW("Setup function is required")
        return false;
    }

    api::view::Dialog dlg(type, ngApp->window());

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
