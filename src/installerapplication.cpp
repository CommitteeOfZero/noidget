#include "installerapplication.h"
#include "installerwindow.h"
#include <api/apihost.h>
#include <api/exception.h>
#include "fs.h"
#include <tx/transaction.h>
#include "receiptwriter.h"
#include "win32_registry.h"
#include <QFile>
#include <QTextStream>
#include <QStyleFactory>
#include <QResource>
#include <QMessageBox>

InstallerApplication::InstallerApplication(int& argc, char** argv)
    : QApplication(argc, argv) {
    // Despite Q_ENUM this is apparently required for use in signals
    qRegisterMetaType<InstallerApplication::State>(
        "InstallerApplication::State");

    _currentState = State::Preparation;

    if (!QResource::registerResource("userdata.rcc")) {
        QMessageBox::critical(0, "Error",
                              "Could not load userdata.rcc (are you running "
                              "the installer out of its directory?)");
        exit(1);
        return;
    }

    w = new InstallerWindow(0);

    // we do not set these globally so that we can have unthemed dialogs
    w->setStyle(QStyleFactory::create("windows"));
    QFile qssFile(":/kofuna/style.qss");
    qssFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&qssFile);
    w->setStyleSheet(ts.readAll());

    h = new api::ApiHost(0);

    _fs = new Fs(this);
#ifdef Q_OS_WIN32
    _registry = new Registry(this);
#endif

    _receipt = new ReceiptWriter(this);

    _tx = new Transaction(this);

    QFile scriptFile(":/userdata/script.js");
    scriptFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts2(&scriptFile);

    QJSValue result = h->engine()->evaluate(ts2.readAll(), "script.js");
    api::reportIfScriptError(result);
}

InstallerApplication::~InstallerApplication() {
    if (w) delete w;
    if (h) delete h;
}

void InstallerApplication::showWindow() { w->show(); }