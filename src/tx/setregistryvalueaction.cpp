#include "setregistryvalueaction.h"
#include "installerapplication.h"
#include "util/exception.h"

#ifdef Q_OS_WIN32

void SetRegistryValueAction::run() {
    if (!ngApp->registry()->setValue(_root, _key, _use64bit, _valName,
                                     _value)) {
        throw NgException(
            QString("Failed to set registry value '%1' in '%2' (64-bit: %3)")
                .arg(_valName, _key)
                .arg(_use64bit));
    }
}

#endif