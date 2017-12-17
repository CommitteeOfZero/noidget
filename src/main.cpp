#include "installerwindow.h"
#include "installerapplication.h"
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[]) {
    QApplication::setDesktopSettingsAware(false);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setStyle("windows");

    InstallerApplication a(argc, argv);

    QFile qssFile(":/kofuna/style.qss");
    qssFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&qssFile);
    a.setStyleSheet(ts.readAll());

    a.showWindow();

    return a.exec();
}
