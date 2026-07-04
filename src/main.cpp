#include "installerwindow.h"
#include "installerapplication.h"

int main(int argc, char *argv[]) {
    QApplication::setDesktopSettingsAware(false);

    InstallerApplication a(argc, argv);

    a.showWindow();

    return a.exec();
}
