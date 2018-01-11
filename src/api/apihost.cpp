#include <QScriptValue>
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

    root_.setProperty("systemInfo", _engine->newQObject(new SystemInfo(this)));

    _engine->globalObject().setProperty("ng", root_);
}

QScriptValue ApiHost::root() { return _engine->globalObject().property("ng"); }

ApiHost::~ApiHost() {}

}  // namespace api