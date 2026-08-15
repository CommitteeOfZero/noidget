#include "win32.h"
#include "apihost.h"
#include "installerapplication.h"

#ifdef Q_OS_WIN32

namespace api {

Win32::Win32(ApiHost *parent) : QObject(parent) {
    qRegisterMetaType<Registry *>("Registry*");
}
Win32::~Win32() {}

void Win32::setupScriptObject(QJSValue &o) {
    ApiHost::registerEnum<Registry::RootKey>(qjsEngine(this), o);
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
