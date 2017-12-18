#include "installerwindow.h"
#include "installerapplication.h"

int main(int argc, char *argv[]) {
    QApplication::setDesktopSettingsAware(false);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setStyle("windows");

    InstallerApplication a(argc, argv);

    a.showWindow();

    return a.exec();
}
