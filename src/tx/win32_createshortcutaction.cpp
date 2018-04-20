#include "createshortcutaction.h"

#ifdef Q_OS_WIN32
#include "windows.h"
#include "winnls.h"
#include "shobjidl.h"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"

#include <QFileInfo>
#include "fs.h"
#include "installerapplication.h"
#include "util/exception.h"

void CreateShortcutAction::run() {
    if (_targetPath.isEmpty() || _shortcutPath.isEmpty()) {
        throw NgException(
            "Missing required parameter trying to create shortcut");
    }

    HRESULT hres;
    IShellLink* psl;

    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                            IID_IShellLink, (LPVOID*)&psl);
    if (SUCCEEDED(hres)) {
        IPersistFile* ppf;

        psl->SetPath(
            (LPCWSTR)ngApp->globalFs()->expandedPath(_targetPath).utf16());
        if (!_targetArgs.isEmpty()) {
            psl->SetArguments((LPCWSTR)_targetArgs.utf16());
        }
        if (!_workingDir.isEmpty()) {
            psl->SetWorkingDirectory(
                (LPCWSTR)ngApp->globalFs()->expandedPath(_workingDir).utf16());
        }
        if (!_iconPath.isEmpty()) {
            psl->SetIconLocation(
                (LPCWSTR)ngApp->globalFs()->expandedPath(_iconPath).utf16(), 0);
        }
        if (!_tooltip.isEmpty()) {
            psl->SetDescription((LPCWSTR)_tooltip.utf16());
        }

        hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

        if (SUCCEEDED(hres)) {
            ngApp->globalFs()->createDirectory(
                QFileInfo(ngApp->globalFs()->expandedPath(_shortcutPath))
                    .path());
            hres = ppf->Save((LPCOLESTR)ngApp->globalFs()
                                 ->expandedPath(_shortcutPath)
                                 .utf16(),
                             TRUE);
            if (!SUCCEEDED(hres)) {
                ppf->Release();
                psl->Release();
                throw NgException(QString("Failed to save shortcut at %1")
                                      .arg(_shortcutPath));
            }
            ppf->Release();
        } else {
            psl->Release();
            throw NgException("Failed to create shortcut");
        }
        psl->Release();
    } else {
        throw NgException("Failed to create shortcut");
    }
}

#endif