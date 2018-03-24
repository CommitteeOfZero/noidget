#pragma once

#include <QApplication>
#include <QCoreApplication>
#include <QStyle>

class InstallerWindow;
class Fs;
class Transaction;
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
    Transaction* tx() { return _tx; }

   private:
    InstallerWindow* w;
    api::ApiHost* h;
    Fs* _fs;
    Transaction* _tx;
};