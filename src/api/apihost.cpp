#include <QScriptValue>
#include <QFile>
#include <QTextStream>
#include "apihost.h"
#include "window.h"
#include "viewhost.h"
#include "systeminfo.h"

namespace api {

ApiHost::ApiHost(QObject *parent) : QObject(parent) {
    _engine = new QScriptEngine(this);
    QScriptValue root_ = _engine->newObject();

    root_.setProperty("window", _engine->newQObject(new Window(this)));

    auto viewHost = new ViewHost(this);
    auto ng_view = _engine->newQObject(viewHost);
    viewHost->setupScriptObject(ng_view);
    root_.setProperty("view", ng_view);

    auto systemInfo = new SystemInfo(this);
    auto ng_systemInfo = _engine->newQObject(systemInfo);
    systemInfo->setupScriptObject(ng_systemInfo);
    root_.setProperty("systemInfo", ng_systemInfo);

    _engine->globalObject().setProperty("ng", root_);

    QFile jslibFile(":/jslib.js");
    jslibFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&jslibFile);
    _engine->evaluate(ts.readAll());
}

QScriptValue ApiHost::root() { return _engine->globalObject().property("ng"); }

ApiHost::~ApiHost() {}

}  // namespace api