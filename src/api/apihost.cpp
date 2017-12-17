#include <QScriptValue>
#include "apihost.h"
#include "window.h"
#include "viewhost.h"

namespace api {

ApiHost::ApiHost(QObject *parent) : QObject(parent) {
    _engine = new QScriptEngine(this);
    QScriptValue root_ = _engine->newObject();

    root_.setProperty("window", _engine->newQObject(new Window(this)));
    root_.setProperty("view", _engine->newQObject(new ViewHost(this)));

    _engine->globalObject().setProperty("ng", root_);
}

QScriptValue ApiHost::root() { return _engine->globalObject().property("ng"); }

ApiHost::~ApiHost() {}

}  // namespace api