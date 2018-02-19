#include "systeminfo.h"
#include "apihost.h"
#include <api/exception.h>
#include <QScriptValue>
#include <QScriptValueList>

namespace api {

SystemInfo::SystemInfo(ApiHost* parent) : QObject(parent) {}
SystemInfo::~SystemInfo() {}

void SystemInfo::setupScriptObject(QScriptValue& o) {
    ApiHost::registerEnum<util::SystemInfo::OsFamily>(o);
}

/*^jsdoc
 * Platform the program is currently running on.
 * @method platform
 * @memberof ng.systemInfo
 * @static
 * @returns {ng.systemInfo.OsFamily}
 ^jsdoc*/
util::SystemInfo::OsFamily SystemInfo::platform() const {
    return util::SystemInfo::platform();
}

}  // namespace api
