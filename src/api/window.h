#pragma once

#include <QObject>
#include <QString>
#include <QScriptable>
#include <QUrl>

namespace api {

class ApiHost;

namespace view {
class Page;
}

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
};
}  // namespace api