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

/*^jsdoc
 * Is the installer a Windows build running under Wine?
 * @method isWine
 * @memberof ng.systemInfo
 * @static
 * @returns {boolean}
 ^jsdoc*/
bool SystemInfo::isWine() const { return util::SystemInfo::isWine(); }

}  // namespace api
