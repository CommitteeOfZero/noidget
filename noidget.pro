QT += core gui widgets script concurrent

TARGET = noidget
TEMPLATE = app

CONFIG += force_debug_info

# miniaudio's feature detection for AVX is (or was) apparently broken, tries to use AVX on i7 930
DEFINES += MA_NO_AVX MA_NO_AVX2 MA_NO_AVX512

win32 {
    CONFIG += embed_manifest_exe
    QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:level=\'requireAdministrator\'
    # registry, shortcuts
    DEFINES += WIN32_LEAN_AND_MEAN PSAPI_VERSION=1
    LIBS += Advapi32.lib Shell32.lib Ole32.lib Psapi.lib
}

CONFIG(scriptdebug) {
    DEFINES += SCRIPT_DEBUG
    QT += scripttools
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# This crap lets us run files with the same name, in the same project, through moc, without conflicts.
# Good idea? Probably not.

CONFIG += object_parallel_to_source
CONFIG += no_batch # above doesn't properly work with nmake without this

defineReplace(fnPath) {
    variable = $$1
    variable = $$replace(variable, $$basename(variable), "")
    variable = $$replace(variable, "\\\\", "_")
    variable = $$replace(variable, "\.", "_")
    variable = $$replace(variable, "/", "_")
    return($$variable)
}

QMAKE_H_MOD_MOC = moc_${QMAKE_FUNC_fnPath}
QMAKE_CPP_MOD_MOC = moc_${QMAKE_FUNC_fnPath}
QMAKE_MOD_RCC = qrc${QMAKE_FUNC_fnPath}

# But I'm going with it anyway.

include(conf.pri)
include(kofuna/kofuna.pri)

INCLUDEPATH += src

SOURCES += $$files(src/*.cpp, true)
SOURCES += $$files(src/*.c, true)
HEADERS += $$files(src/*.h, true)
FORMS += $$files(src/*.ui, true)

RESOURCES += \
    main.qrc
