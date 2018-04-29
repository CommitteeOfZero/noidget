#include "installerapplication.h"
#include "installerwindow.h"
#include <api/apihost.h>
#include "fs.h"
#include <tx/transaction.h>
#include "receipt.h"
#include "win32_registry.h"
#include <QFile>
#include <QTextStream>
#include <QStyleFactory>
#include <QResource>

#ifdef QT_DEBUG
#include <QScriptEngineDebugger>
#include <QAction>
#endif

InstallerApplication::InstallerApplication(int& argc, char** argv)
    : QApplication(argc, argv) {
    // Despite Q_ENUM this is apparently required for use in signals
    qRegisterMetaType<InstallerApplication::State>(
        "InstallerApplication::State");

    _currentState = State::Preparation;

    QResource::registerResource("userdata.rcc");

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

    _receipt = new Receipt(this);

    _tx = new Transaction(this);

    QFile scriptFile(":/userdata/script.js");
    scriptFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts2(&scriptFile);
#ifdef QT_DEBUG
    QScriptEngineDebugger* debugger = new QScriptEngineDebugger(this);
    debugger->attachTo(h->engine());
    #if 0
    debugger->action(QScriptEngineDebugger::InterruptAction)->trigger();
    #endif
#endif
    h->engine()->evaluate(ts2.readAll());
}

InstallerApplication::~InstallerApplication() {
    delete w;
    delete h;
}

void InstallerApplication::showWindow() { w->show(); }