#include "txhost.h"
#include "apihost.h"
#include "tx/transaction.h"
#include "tx/txsection.h"
#include "tx/txaction.h"
#include "tx/copyfilesaction.h"
#include "tx/logaction.h"
#include "tx/createdirectoryaction.h"
#include "installerapplication.h"
#include "progresspage.h"
#include "installerwindow.h"
#include <api/exception.h>

static void modifyTransactionInstance(QScriptValue &o) {
    // TODO stream builders
}
/*  TODO:

    Q_INVOKABLE void buildMpk(const QString& path);
    Q_INVOKABLE void streamOpen(void* stream);
    Q_INVOKABLE void streamClose(void* stream);
    Q_INVOKABLE void streamSeek(void* stream, qint64 bytes);
    Q_INVOKABLE void streamWriter(void* stream, const QString& path);
    Q_INVOKABLE void binarySearchReplace(const QString& path,
                                         const QString& needle,
                                         const QString& replace);
    */
static QScriptValue txSectionCopyFiles(QScriptContext *context,
                                       QScriptEngine *engine);
static QScriptValue txSectionLog(QScriptContext *context,
                                 QScriptEngine *engine);
static QScriptValue txSectionCreateDirectory(QScriptContext *context,
                                             QScriptEngine *engine);
static void modifyTxSectionInstance(QScriptValue &o) {
    o.setProperty("copyFiles", o.engine()->newFunction(txSectionCopyFiles));
    o.setProperty("log", o.engine()->newFunction(txSectionLog));
    o.setProperty("createDirectory",
                  o.engine()->newFunction(txSectionCreateDirectory));
}

QScriptValue transactionToScriptValue(QScriptEngine *engine,
                                      Transaction *const &in) {
    auto ret = engine->newQObject(in);
    modifyTransactionInstance(ret);
    return ret;
}
void transactionFromScriptValue(const QScriptValue &object, Transaction *&out) {
    out = qobject_cast<Transaction *>(object.toQObject());
}
QScriptValue txSectionToScriptValue(QScriptEngine *engine,
                                    TxSection *const &in) {
    auto ret = engine->newQObject(in);
    modifyTxSectionInstance(ret);
    return ret;
}
void txSectionFromScriptValue(const QScriptValue &object, TxSection *&out) {
    out = qobject_cast<TxSection *>(object.toQObject());
}
QScriptValue txActionToScriptValue(QScriptEngine *engine, TxAction *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void txActionFromScriptValue(const QScriptValue &object, TxAction *&out) {
    out = qobject_cast<TxAction *>(object.toQObject());
}
QScriptValue copyFilesActionToScriptValue(QScriptEngine *engine,
                                          CopyFilesAction *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void copyFilesActionFromScriptValue(const QScriptValue &object,
                                    CopyFilesAction *&out) {
    out = qobject_cast<CopyFilesAction *>(object.toQObject());
}
QScriptValue logActionToScriptValue(QScriptEngine *engine,
                                    LogAction *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void logActionFromScriptValue(const QScriptValue &object, LogAction *&out) {
    out = qobject_cast<LogAction *>(object.toQObject());
}
QScriptValue createDirectoryActionToScriptValue(
    QScriptEngine *engine, CreateDirectoryAction *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void createDirectoryActionFromScriptValue(const QScriptValue &object,
                                          CreateDirectoryAction *&out) {
    out = qobject_cast<CreateDirectoryAction *>(object.toQObject());
}

/*^jsdoc
 * Adds a file copy operation to the section.
 * 
 * `src` can be a directory (in which case the directory is copied to `dest` whole),
 * `/path/to/some/directory/*` (in which case all of its files and subdirectories
 * are copied to the `dest` directory), or a single file (copied into `dest` if that 
 * refers to a directory, or named `dest` otherwise).
 * 
 * Destination directory (and parents) do not need to exist and existing files
 * will be overwritten.
 * 
 * @method copyFiles
 * @param {string} src
 * @param {string} dest
 * @memberof ng.tx.TxSection
 * @instance
 ^jsdoc*/
static QScriptValue txSectionCopyFiles(QScriptContext *context,
                                       QScriptEngine *engine) {
    QScriptValue _this = context->thisObject();
    TxSection *section;
    txSectionFromScriptValue(_this, section);
    QScriptValue ret;
    if (context->argumentCount() < 2) {
        SCRIPT_THROW_FUN("Missing required parameter")
        return ret;
    }
    QScriptValue src = context->argument(0);
    QScriptValue dest = context->argument(1);
    if (!src.isString() || !dest.isString()) {
        SCRIPT_THROW_FUN("Parameter has invalid type")
        return ret;
    }
    SCRIPT_EX_GUARD_START_FUN
    CopyFilesAction *action = new CopyFilesAction(section);
    action->setSrc(src.toString());
    action->setDest(dest.toString());
    section->addAction(action);
    ret = copyFilesActionToScriptValue(engine, action);
    SCRIPT_EX_GUARD_END_FUN(ret)
    return ret;
}

/*^jsdoc
 * Write plain text to the log during section
 * 
 * Rich text is not supported. Text will be displayed in the UI and written to
 * the plaintext log file.
 * 
 * @method log
 * @param {string} text
 * @memberof ng.tx.TxSection
 * @instance
 ^jsdoc*/
static QScriptValue txSectionLog(QScriptContext *context,
                                 QScriptEngine *engine) {
    QScriptValue _this = context->thisObject();
    TxSection *section;
    txSectionFromScriptValue(_this, section);
    QScriptValue ret;
    if (context->argumentCount() < 1) {
        SCRIPT_THROW_FUN("Missing required parameter")
        return ret;
    }
    QScriptValue text = context->argument(0);
    if (!text.isString()) {
        SCRIPT_THROW_FUN("Parameter has invalid type")
        return ret;
    }
    SCRIPT_EX_GUARD_START_FUN
    LogAction *action = new LogAction(section);
    action->setText(text.toString());
    section->addAction(action);
    ret = logActionToScriptValue(engine, action);
    SCRIPT_EX_GUARD_END_FUN(ret)
    return ret;
}

/*^jsdoc
 * Create directory operation
 * 
 * Parent directories will be created when this is executed.
 * 
 * @method createDirectory
 * @param {string} path
 * @memberof ng.tx.TxSection
 * @instance
 ^jsdoc*/
static QScriptValue txSectionCreateDirectory(QScriptContext *context,
                                             QScriptEngine *engine) {
    QScriptValue _this = context->thisObject();
    TxSection *section;
    txSectionFromScriptValue(_this, section);
    QScriptValue ret;
    if (context->argumentCount() < 1) {
        SCRIPT_THROW_FUN("Missing required parameter")
        return ret;
    }
    QScriptValue path = context->argument(0);
    if (!path.isString()) {
        SCRIPT_THROW_FUN("Parameter has invalid type")
        return ret;
    }
    SCRIPT_EX_GUARD_START_FUN
    CreateDirectoryAction *action = new CreateDirectoryAction(section);
    action->setPath(path.toString());
    section->addAction(action);
    ret = createDirectoryActionToScriptValue(engine, action);
    SCRIPT_EX_GUARD_END_FUN(ret)
    return ret;
}

namespace api {
TxHost::TxHost(ApiHost *parent) : QObject(parent) {
    QScriptEngine *engine = parent->engine();
    qScriptRegisterMetaType(engine, transactionToScriptValue,
                            transactionFromScriptValue);
    qScriptRegisterMetaType(engine, txSectionToScriptValue,
                            txSectionFromScriptValue);
    qScriptRegisterMetaType(engine, txActionToScriptValue,
                            txActionFromScriptValue);
    qScriptRegisterMetaType(engine, copyFilesActionToScriptValue,
                            copyFilesActionFromScriptValue);
    qScriptRegisterMetaType(engine, logActionToScriptValue,
                            logActionFromScriptValue);
    qScriptRegisterMetaType(engine, createDirectoryActionToScriptValue,
                            createDirectoryActionFromScriptValue);
}
void TxHost::setupScriptObject(QScriptValue &o) {}
TxHost::~TxHost() {}

/*^jsdoc
 * Returns the global {@link ng.tx.Transaction} instance.
 * @method tx
 * @memberof ng.tx
 * @static
 * @returns {ng.tx.Transaction}
 ^jsdoc*/
Transaction *TxHost::tx() { return ngApp->tx(); }

/*^jsdoc
 * Moves to the progress page and starts the installation. **This must be
 * the last thing you call** in the whole script.
 * @method run
 * @memberof ng.tx
 * @static
 ^jsdoc*/
void TxHost::run() {
    ProgressPage *page = new ProgressPage(0);
    ngApp->window()->push(page);
}

}  // namespace api