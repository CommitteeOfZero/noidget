#include "installerwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[]) {
    QApplication::setDesktopSettingsAware(false);
    QApplication::setStyle("windows");

    QApplication a(argc, argv);
    InstallerWindow w;
    w.show();

    QFile qssFile(":/kofuna/style.qss");
    qssFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&qssFile);
    a.setStyleSheet(ts.readAll());

    return a.exec();
}
