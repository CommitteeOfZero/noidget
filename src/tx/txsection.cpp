#include "txsection.h"
#include "txaction.h"
#include "copyfilesaction.h"
#include "logaction.h"
#include "createdirectoryaction.h"
#include "streamopenaction.h"
#include "streamcloseaction.h"
#include "streamseekaction.h"
#include "writestreamaction.h"
#include "buildmpkaction.h"
#include "binarysearchreplaceaction.h"
#ifdef Q_OS_WIN32
#include "setregistryvalueaction.h"
#endif
#include "createshortcutaction.h"
#include "removedirectoryaction.h"
#include "rollbackreceiptaction.h"
#include "removefileaction.h"
#include <api/exception.h>

TxSection::TxSection(QObject* parent = 0) : QObject(parent) {}
TxSection::~TxSection() {}

void TxSection::addAction(TxAction* action) {
    action->setParent(this);
    connect(action, &TxAction::log, this, &TxSection::actionLog,
            Qt::DirectConnection);
    connect(this, &TxSection::cancelled, action, &TxAction::cancel);
    _actions.append(action);
    int i = _actions.count() - 1;
    connect(action, &TxAction::progress, [i, this](qint64 actionProgress) {
        actionProgress = qMin(_actionSizes[i], actionProgress);
        emit progress(_roughProgress + actionProgress);
    });
    connect(
        action, &TxAction::subactionProgress, [i, this](qint64 actionProgress) {
            actionProgress = qMin(_actionSubactionCounts[i], actionProgress);
            emit subactionProgress(_roughSubactionProgress + actionProgress);
        });
}

qint64 TxSection::size() {
    qint64 result = 0;
    for (TxAction* action : _actions) {
        qint64 actionSize = action->size();
        _actionSizes.append(actionSize);
        result += actionSize;
    }
    return result;
}

qint64 TxSection::subactionCount() {
    qint64 result = 0;
    for (TxAction* action : _actions) {
        qint64 subactionCount = action->subactionCount();
        _actionSubactionCounts.append(subactionCount);
        result += subactionCount;
    }
    return result;
}

void TxSection::prepare() {
    for (TxAction* action : _actions) {
        action->prepare();
    }
}

void TxSection::run() {
    for (int i = 0; i < _actions.count(); i++) {
        if (_isCancelled) {
            return;
        }
        TxAction* action = _actions[i];
        action->run();
        _roughProgress += _actionSizes[i];
        _roughSubactionProgress += _actionSubactionCounts[i];
        emit progress(_roughProgress);
        emit subactionProgress(_roughSubactionProgress);
    }
}

void TxSection::actionLog(const QString& text, bool fileOnly) {
    emit actionLogged(text, fileOnly);
}

CopyFilesAction* TxSection::copyFiles(const QString& src,
                                      const QString& dest) {
    SCRIPT_EX_GUARD_START
    CopyFilesAction* action = new CopyFilesAction(this);
    action->setSrc(src);
    action->setDest(dest);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

LogAction* TxSection::log(const QString& text, bool fileOnly) {
    SCRIPT_EX_GUARD_START
    LogAction* action = new LogAction(this);
    action->setText(text);
    action->setFileOnly(fileOnly);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

CreateDirectoryAction* TxSection::createDirectory(const QString& path) {
    SCRIPT_EX_GUARD_START
    CreateDirectoryAction* action = new CreateDirectoryAction(this);
    action->setPath(path);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

StreamOpenAction* TxSection::streamOpen(TxStream* stream) {
    SCRIPT_EX_GUARD_START
    StreamOpenAction* action = new StreamOpenAction(this);
    action->setStream(stream);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

StreamCloseAction* TxSection::streamClose(TxStream* stream) {
    SCRIPT_EX_GUARD_START
    StreamCloseAction* action = new StreamCloseAction(this);
    action->setStream(stream);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

StreamSeekAction* TxSection::streamSeek(TxStream* stream, qint64 count) {
    SCRIPT_EX_GUARD_START
    StreamSeekAction* action = new StreamSeekAction(this);
    action->setStream(stream);
    action->setCount(count);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

WriteStreamAction* TxSection::writeStream(TxStream* stream,
                                          const QString& dest,
                                          qint64 count) {
    SCRIPT_EX_GUARD_START
    WriteStreamAction* action = new WriteStreamAction(this);
    action->setStream(stream);
    action->setDest(dest);
    if (count != 0) {
        action->setCount(count);
    }
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

BuildMpkAction* TxSection::buildMpk(const QString& path) {
    SCRIPT_EX_GUARD_START
    BuildMpkAction* action = new BuildMpkAction(this);
    action->setPath(path);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

BinarySearchReplaceAction* TxSection::binarySearchReplace(
    const QString& path, const QString& needle, const QString& replace) {
    SCRIPT_EX_GUARD_START
    BinarySearchReplaceAction* action = new BinarySearchReplaceAction(this);
    action->setPath(path);
    action->setNeedle(needle);
    action->setReplace(replace);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

#ifdef Q_OS_WIN32
SetRegistryValueAction* TxSection::setRegistryValue(
    Registry::RootKey root, const QString& key, bool use64bit,
    const QString& valName, const QVariant& value) {
    SCRIPT_EX_GUARD_START
    SetRegistryValueAction* action = new SetRegistryValueAction(this);
    action->setRoot(root);
    action->setKey(key);
    action->setUse64bit(use64bit);
    action->setValName(valName);
    action->setValue(value);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}
#endif

CreateShortcutAction* TxSection::createShortcut(const QJSValue& params) {
    SCRIPT_EX_GUARD_START
    CreateShortcutAction* action = new CreateShortcutAction(this);
    action->setShortcutPath(params.property("shortcutPath").toString());
    action->setTargetPath(params.property("targetPath").toString());
    if (params.property("version").isString()) {
        action->setVersion(params.property("version").toString());
    }
    if (params.property("displayName").isString()) {
        action->setDisplayName(params.property("displayName").toString());
    }
    if (params.property("targetArgs").isString()) {
        action->setTargetArgs(params.property("targetArgs").toString());
    }
    if (params.property("workingDir").isString()) {
        action->setWorkingDir(params.property("workingDir").toString());
    }
    if (params.property("iconPath").isString()) {
        action->setIconPath(params.property("iconPath").toString());
    }
    if (params.property("tooltip").isString()) {
        action->setTooltip(params.property("tooltip").toString());
    }
    if (params.property("xdgCategories").isString()) {
        action->setXdgCategories(params.property("xdgCategories").toString());
    }
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

RemoveDirectoryAction* TxSection::removeDirectory(const QString& path,
                                                  bool onlyIfEmpty) {
    SCRIPT_EX_GUARD_START
    RemoveDirectoryAction* action = new RemoveDirectoryAction(this);
    action->setPath(path);
    action->setOnlyIfEmpty(onlyIfEmpty);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

RollbackReceiptAction* TxSection::rollbackReceipt() {
    SCRIPT_EX_GUARD_START
    RollbackReceiptAction* action = new RollbackReceiptAction(this);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}

RemoveFileAction* TxSection::removeFile(const QString& path) {
    SCRIPT_EX_GUARD_START
    RemoveFileAction* action = new RemoveFileAction(this);
    action->setPath(path);
    addAction(action);
    return action;
    SCRIPT_EX_GUARD_END(nullptr)
}
