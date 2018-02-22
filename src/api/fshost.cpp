#include "fshost.h"
#include "apihost.h"
#include "fs.h"
#include <api/exception.h>

QScriptValue fsToScriptValue(QScriptEngine *engine, Fs *const &in) {
    return engine->newQObject(in);
}
void fsFromScriptValue(const QScriptValue &object, Fs *&out) {
    out = qobject_cast<Fs *>(object.toQObject());
}

namespace api {
FsHost::FsHost(ApiHost *parent) : QObject(parent) {
    QScriptEngine *engine = parent->engine();
    qScriptRegisterMetaType(engine, fsToScriptValue, fsFromScriptValue);
}
void FsHost::setupScriptObject(QScriptValue &o) {}
FsHost::~FsHost() {}

/*^jsdoc
 * Creates a new {@link ng.fs.Fs}
 * @method createFs
 * @memberof ng.fs
 * @static
 * @returns {ng.fs.Fs}
 ^jsdoc*/
QScriptValue FsHost::createFs() {
    ENFORCE_SCRIPT
    Fs *fs = new Fs();
    return context()->engine()->newQObject(fs, QScriptEngine::ScriptOwnership);
}
}  // namespace api