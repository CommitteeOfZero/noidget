#include "installerapplication.h"
#include "installerwindow.h"
#include <api/apihost.h>
#include <QFile>
#include <QTextStream>
#include <QStyleFactory>

InstallerApplication::InstallerApplication(int& argc, char** argv)
    : QApplication(argc, argv) {
    auto defaultStyleName = style()->objectName();
    _defaultStyle = QStyleFactory::create(defaultStyleName);

    setStyle("windows");
    QFile qssFile(":/kofuna/style.qss");
    qssFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&qssFile);
    setStyleSheet(ts.readAll());

    w = new InstallerWindow(0);

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