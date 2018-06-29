#include "systeminfo.h"

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

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

bool SystemInfo::isWine() {
#ifndef Q_OS_WIN32
    return false;
#else
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if (!ntdll) return false;
    return GetProcAddress(ntdll, "wine_get_version") != NULL;
#endif
}

}  // namespace util
