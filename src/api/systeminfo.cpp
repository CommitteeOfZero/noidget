#include "systeminfo.h"
#include "apihost.h"
#include <api/exception.h>
#include <QScriptValue>
#include <QScriptValueList>

namespace api {

SystemInfo::SystemInfo(ApiHost *parent) : QObject(parent) {}
SystemInfo::~SystemInfo() {}

QString SystemInfo::platform() const {
#if defined(Q_OS_WIN32)
    return "win32";
#elif defined(Q_OS_MACOS)
    return "mac";
#elif defined(Q_OS_LINUX)
    return "linux";
#else
    return "wtf";
#endif
}

}  // namespace api
