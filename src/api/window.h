#pragma once

#include <QObject>
#include <QString>
#include <QScriptable>
#include <QUrl>
#include <QPixmap>
#include <api/view/dialog.h>

namespace api {

class ApiHost;

namespace view {
class Page;
}  // namespace view

/*^jsdoc
 * @namespace window
 * @memberof ng
 * @static
 * @toplevel
 ^jsdoc*/
class Window : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit Window(ApiHost* parent);
    ~Window();

    Q_INVOKABLE api::view::Page* createPage(const QString& title);
    Q_INVOKABLE void pushPage(api::view::Page* page);
    Q_INVOKABLE void popPage();

    Q_INVOKABLE void playBgm(const QScriptValue& v);
    Q_INVOKABLE void setMessageBoxIcon(const QString& url);
    Q_INVOKABLE void setTitle(const QString& title);

    Q_INVOKABLE void messageBox(const QScriptValue& v);
    Q_INVOKABLE bool modal(api::view::Dialog::DlgType type,
                           const QScriptValue& setup);

   private:
    QPixmap _mbIcon;
};
}  // namespace api