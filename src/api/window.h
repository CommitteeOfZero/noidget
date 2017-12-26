#pragma once

#include <QObject>
#include <QString>
#include <QScriptable>
#include <QUrl>

namespace api {

class ApiHost;

namespace view {
class Page;
}  // namespace view

/*^jsdoc
 * @name window
 * @memberof ng
 * @namespace
 * @static
 * @toplevel
 ^jsdoc*/
/*^jsdoc
 * @method popPage
 * memberof ng.window
 * @static
 ^jsdoc*/
class Window : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit Window(ApiHost* parent);
    ~Window();

    Q_INVOKABLE api::view::Page* createPage(const QString& title);
    Q_INVOKABLE void pushPage(api::view::Page* page);
    Q_INVOKABLE void popPage();

    Q_INVOKABLE void playBgm(const QString& url);

    Q_INVOKABLE void messageBox(const QScriptValue& v);
    Q_INVOKABLE bool modal(const QString& type, const QScriptValue& setup);
};
}  // namespace api