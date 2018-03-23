#pragma once

#include <QApplication>
#include <QCoreApplication>
#include <QStyle>

class InstallerWindow;
class Fs;
namespace api {
class ApiHost;
}

#define ngApp static_cast<::InstallerApplication*>(QCoreApplication::instance())

class InstallerApplication : public QApplication {
    Q_OBJECT

   public:
    explicit InstallerApplication(int& argc, char** argv);
    ~InstallerApplication();

    void showWindow();

    InstallerWindow* window() { return w; }
    api::ApiHost* apiHost() { return h; }
    Fs* globalFs() { return _fs; }

   private:
    InstallerWindow* w;
    api::ApiHost* h;
    Fs* _fs;
};