#include "win32.h"
#include "apihost.h"
#include <QScriptValue>
#include <QScriptValueList>
#include "installerapplication.h"

#ifdef Q_OS_WIN32

namespace api {

QScriptValue registryToScriptValue(QScriptEngine *engine, Registry *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void registryFromScriptValue(const QScriptValue &object, Registry *&out) {
    out = qobject_cast<Registry *>(object.toQObject());
}

Win32::Win32(ApiHost *parent) : QObject(parent) {
    QScriptEngine *engine = parent->engine();
    qScriptRegisterMetaType(engine, registryToScriptValue,
                            registryFromScriptValue);
}
Win32::~Win32() {}

void Win32::setupScriptObject(QScriptValue &o) {
    ApiHost::registerEnum<Registry::RootKey>(o);
}

/*^jsdoc
 * Returns a global {@link ng.win32.Registry} instance.
 *
 * @method registry
 * @memberof ng.win32
 * @static
 * @returns {ng.win32.Registry}
 ^jsdoc*/
Registry *Win32::registry() const { return ngApp->registry(); }

}  // namespace api
#endif