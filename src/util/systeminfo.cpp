#include "systeminfo.h"

namespace util {

SystemInfo::OsFamily SystemInfo::platform() {
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

}  // namespace util
