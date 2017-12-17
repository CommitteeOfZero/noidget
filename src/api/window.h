#pragma once

#include <QObject>
#include <QString>
#include <QScriptable>

namespace api {

namespace view {
class Page;
}

class Window : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit Window(QObject* parent = 0);
    ~Window();

    Q_INVOKABLE api::view::Page* createPage(const QString& title);
    Q_INVOKABLE void pushPage(api::view::Page* page);
    Q_INVOKABLE void popPage();

    Q_INVOKABLE void messageBox(const QString& message);
};
}  // namespace api