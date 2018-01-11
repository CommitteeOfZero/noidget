#include "systeminfo.h"
#include "apihost.h"
#include <api/exception.h>
#include <QScriptValue>
#include <QScriptValueList>

namespace api {

SystemInfo::SystemInfo(ApiHost* parent) : QObject(parent) {}
SystemInfo::~SystemInfo() {}

void SystemInfo::setupScriptObject(QScriptValue& o) {
    ApiHost::registerEnum<api::SystemInfo::OsFamily>(o);
}

/*^jsdoc
 * Platform the program is currently running on.
 * @method platform
 * @memberof ng.systemInfo
 * @static
 * @returns {ng.systemInfo.OsFamily}
 ^jsdoc*/
SystemInfo::OsFamily SystemInfo::platform() const {
#if defined(Q_OS_WIN32)
    return OsFamily::Windows;
#elif defined(Q_OS_MACOS)
    return OsFamily::Mac;
#elif defined(Q_OS_LINUX)
    return OsFamily::Linux;
#else
    return OsFamily::Unknown;
#endif
}

}  // namespace api
