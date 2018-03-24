#include "installerapplication.h"
#include "installerwindow.h"
#include <api/apihost.h>
#include "fs.h"
#include <tx/transaction.h>
#include <QFile>
#include <QTextStream>
#include <QStyleFactory>

InstallerApplication::InstallerApplication(int& argc, char** argv)
    : QApplication(argc, argv) {
    w = new InstallerWindow(0);

    // we do not set these globally so that we can have unthemed dialogs
    w->setStyle(QStyleFactory::create("windows"));
    QFile qssFile(":/kofuna/style.qss");
    qssFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&qssFile);
    w->setStyleSheet(ts.readAll());

    h = new api::ApiHost(0);

    _fs = new Fs(this);

    _tx = new Transaction(this);

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