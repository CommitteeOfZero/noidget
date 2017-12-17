#include "installerapplication.h"
#include "installerwindow.h"
#include <api/apihost.h>
#include <QFile>
#include <QTextStream>

InstallerApplication::InstallerApplication(int& argc, char** argv)
    : QApplication(argc, argv) {
    w = new InstallerWindow(0);
    h = new api::ApiHost(0);

    QFile scriptFile(":/script.js");
    scriptFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&scriptFile);
    h->engine()->evaluate(ts.readAll());
}

InstallerApplication::~InstallerApplication() {
    delete w;
    delete h;
}

void InstallerApplication::showWindow() { w->show(); }