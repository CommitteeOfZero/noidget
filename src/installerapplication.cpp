#include "installerapplication.h"
#include "installerwindow.h"
#include <api/apihost.h>
#include <QFile>
#include <QTextStream>

InstallerApplication::InstallerApplication(int& argc, char** argv)
    : QApplication(argc, argv) {
    w = new InstallerWindow(0);

    QFile qssFile(":/kofuna/style.qss");
    qssFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&qssFile);
    setStyleSheet(ts.readAll());

    h = new api::ApiHost(0);

    QFile scriptFile(":/script.js");
    scriptFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts2(&scriptFile);
    h->engine()->evaluate(ts2.readAll());
}

InstallerApplication::~InstallerApplication() {
    delete w;
    delete h;
}

void InstallerApplication::showWindow() { w->show(); }