QT += core gui multimedia widgets

TARGET = noidget
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include(kofuna/kofuna.pri)

SOURCES += \
    main.cpp \
    installerwindow.cpp

HEADERS += \
    installerwindow.h

FORMS += \
    installerwindow.ui

RESOURCES += \
    main.qrc