#include "txhost.h"
#include "apihost.h"
#include "tx/transaction.h"
#include "tx/txsection.h"
#include "tx/txaction.h"
#include "tx/copyfilesaction.h"
#include "tx/logaction.h"
#include "tx/createdirectoryaction.h"
#include "tx/streamopenaction.h"
#include "tx/streamcloseaction.h"
#include "tx/streamseekaction.h"
#include "tx/writestreamaction.h"
#include "tx/buildmpkaction.h"
#include "tx/txfilestream.h"
#include "installerapplication.h"
#include "progresspage.h"
#include "installerwindow.h"
#include <api/exception.h>

static QScriptValue fileStream(QScriptContext *context, QScriptEngine *engine);
static void modifyTransactionInstance(QScriptValue &o) {
    o.setProperty("fileStream", o.engine()->newFunction(fileStream));
}

/*  TODO:
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

static QScriptValue txSectionStreamOpen(QScriptContext *context,
                                        QScriptEngine *engine);

static QScriptValue txSectionStreamClose(QScriptContext *context,
                                         QScriptEngine *engine);

static QScriptValue txSectionStreamSeek(QScriptContext *context,
                                        QScriptEngine *engine);

static QScriptValue txSectionWriteStream(QScriptContext *context,
                                         QScriptEngine *engine);
static void modifyTxSectionInstance(QScriptValue &o) {
    o.setProperty("copyFiles", o.engine()->newFunction(txSectionCopyFiles));
    o.setProperty("log", o.engine()->newFunction(txSectionLog));
    o.setProperty("createDirectory",
                  o.engine()->newFunction(txSectionCreateDirectory));
    o.setProperty("streamOpen", o.engine()->newFunction(txSectionStreamOpen));
    o.setProperty("streamClose", o.engine()->newFunction(txSectionStreamClose));
    o.setProperty("streamSeek", o.engine()->newFunction(txSectionStreamSeek));
    o.setProperty("writeStream", o.engine()->newFunction(txSectionWriteStream));
}

static QScriptValue mpkAddEntry(QScriptContext *context, QScriptEngine *engine);
static void modifyBuildMpkActionInstance(QScriptValue &o) {
    o.setProperty("addEntry", o.engine()->newFunction(mpkAddEntry));
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
QScriptValue streamOpenActionToScriptValue(QScriptEngine *engine,
                                           StreamOpenAction *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void streamOpenActionFromScriptValue(const QScriptValue &object,
                                     StreamOpenAction *&out) {
    out = qobject_cast<StreamOpenAction *>(object.toQObject());
}
QScriptValue streamCloseActionToScriptValue(QScriptEngine *engine,
                                            StreamCloseAction *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void streamCloseActionFromScriptValue(const QScriptValue &object,
                                      StreamCloseAction *&out) {
    out = qobject_cast<StreamCloseAction *>(object.toQObject());
}
QScriptValue streamSeekActionToScriptValue(QScriptEngine *engine,
                                           StreamSeekAction *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void streamSeekActionFromScriptValue(const QScriptValue &object,
                                     StreamSeekAction *&out) {
    out = qobject_cast<StreamSeekAction *>(object.toQObject());
}
QScriptValue writeStreamActionToScriptValue(QScriptEngine *engine,
                                            WriteStreamAction *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void writeStreamActionFromScriptValue(const QScriptValue &object,
                                      WriteStreamAction *&out) {
    out = qobject_cast<WriteStreamAction *>(object.toQObject());
}
QScriptValue buildMpkActionToScriptValue(QScriptEngine *engine,
                                         BuildMpkAction *const &in) {
    auto ret = engine->newQObject(in);
    modifyBuildMpkActionInstance(ret);
    return ret;
}
void buildMpkActionFromScriptValue(const QScriptValue &object,
                                   BuildMpkAction *&out) {
    out = qobject_cast<BuildMpkAction *>(object.toQObject());
}
QScriptValue txStreamToScriptValue(QScriptEngine *engine, TxStream *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void txStreamFromScriptValue(const QScriptValue &object, TxStream *&out) {
    out = qobject_cast<TxStream *>(object.toQObject());
}
QScriptValue txFileStreamToScriptValue(QScriptEngine *engine,
                                       TxFileStream *const &in) {
    auto ret = engine->newQObject(in);
    return ret;
}
void txFileStreamFromScriptValue(const QScriptValue &object,
                                 TxFileStream *&out) {
    out = qobject_cast<TxFileStream *>(object.toQObject());
}

/*^jsdoc
 * Prepare a stream for reading from file
 * 
 * @method fileStream
 * @param {string} inPath
 * @memberof ng.tx
 * @returns {ng.tx.TxFileStream}
 * @static
 ^jsdoc*/
static QScriptValue fileStream(QScriptContext *context, QScriptEngine *engine) {
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
    TxFileStream *stream = new TxFileStream();
    stream->setInPath(path.toString());
    ret = txFileStreamToScriptValue(engine, stream);
    SCRIPT_EX_GUARD_END_FUN(ret)
    return ret;
}

/*^jsdoc
 * Add a file to the archive
 * 
 * @method addEntry
 * @param {Object} params
 * @param {Number} params.id
 * @param {string} params.name - archive-internal file name/path (ISO-8859-1, max. 223 characters)
 * @param {Number} [params.displaySize=0] - file size in bytes (purely for progress indicator, BuildMpkAction always copies all data)
 * @param params.source - either a file path or a {@link ng.tx.TxStream}
 * @memberof ng.tx.BuildMpkAction
 * @instance
 ^jsdoc*/
static QScriptValue mpkAddEntry(QScriptContext *context,
                                QScriptEngine *engine) {
    QScriptValue _this = context->thisObject();
    BuildMpkAction *action;
    buildMpkActionFromScriptValue(_this, action);
    QScriptValue ret;
    if (context->argumentCount() < 1) {
        SCRIPT_THROW_FUN("Missing required parameter")
        return ret;
    }
    QScriptValue obj = context->argument(0);
    if (!obj.isObject()) {
        SCRIPT_THROW_FUN("Parameter has invalid type")
        return ret;
    }
    if (!obj.property("id").isNumber() || !obj.property("name").isString() ||
        (!obj.property("source").isString() &&
         (!obj.property("source").isQObject() ||
          qobject_cast<TxStream *>(obj.property("source").toQObject()) == 0))) {
        SCRIPT_THROW_FUN("Missing required parameter / invalid type")
        return ret;
    }
    int id = obj.property("id").toInt32();
    QString name = obj.property("name").toString();
    qint64 displaySize = 0;
    if (obj.property("displaySize").isNumber()) {
        displaySize = (qint64)obj.property("displaySize").toInteger();
    }
    SCRIPT_EX_GUARD_START_FUN
    if (obj.property("source").isString()) {
        QString path = obj.property("source").toString();
        action->addEntry(id, name, path, displaySize);
    } else {
        TxStream *stream =
            qobject_cast<TxStream *>(obj.property("source").toQObject());
        action->addEntry(id, name, stream, displaySize);
    }
    SCRIPT_EX_GUARD_END_FUN(ret)
    return ret;
}

/*^jsdoc
 * File copy operation
 * 
 * @method copyFiles
 * @param {string} src
 * @param {string} dest
 * @memberof ng.tx.TxSection
 * @returns {ng.tx.CopyFilesAction}
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
 * @method log
 * @param {string} text
 * @memberof ng.tx.TxSection
 * @returns {ng.tx.LogAction}
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
 * @returns {ng.tx.CreateDirectoryAction}
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

/*^jsdoc
 * Queue the opening of a stream
 * 
 * @method streamOpen
 * @param {ng.tx.TxStream} stream
 * @memberof ng.tx.TxSection
 * @returns {ng.tx.StreamOpenAction}
 * @instance
 ^jsdoc*/
static QScriptValue txSectionStreamOpen(QScriptContext *context,
                                        QScriptEngine *engine) {
    QScriptValue _this = context->thisObject();
    TxSection *section;
    txSectionFromScriptValue(_this, section);
    QScriptValue ret;
    if (context->argumentCount() < 1) {
        SCRIPT_THROW_FUN("Missing required parameter")
        return ret;
    }
    QScriptValue _stream = context->argument(0);
    TxStream *stream;
    if (!_stream.isQObject() ||
        (stream = qobject_cast<TxStream *>(_stream.toQObject())) == 0) {
        SCRIPT_THROW_FUN("Parameter has invalid type")
        return ret;
    }
    SCRIPT_EX_GUARD_START_FUN
    StreamOpenAction *action = new StreamOpenAction(section);
    action->setStream(stream);
    section->addAction(action);
    ret = streamOpenActionToScriptValue(engine, action);
    SCRIPT_EX_GUARD_END_FUN(ret)
    return ret;
}

/*^jsdoc
 * Queue the closing of a previously opened stream
 * 
 * @method streamClose
 * @param {ng.tx.TxStream} stream
 * @memberof ng.tx.TxSection
 * @returns {ng.tx.StreamCloseAction}
 * @instance
 ^jsdoc*/
static QScriptValue txSectionStreamClose(QScriptContext *context,
                                         QScriptEngine *engine) {
    QScriptValue _this = context->thisObject();
    TxSection *section;
    txSectionFromScriptValue(_this, section);
    QScriptValue ret;
    if (context->argumentCount() < 1) {
        SCRIPT_THROW_FUN("Missing required parameter")
        return ret;
    }
    QScriptValue _stream = context->argument(0);
    TxStream *stream;
    if (!_stream.isQObject() ||
        (stream = qobject_cast<TxStream *>(_stream.toQObject())) == 0) {
        SCRIPT_THROW_FUN("Parameter has invalid type")
        return ret;
    }
    SCRIPT_EX_GUARD_START_FUN
    StreamCloseAction *action = new StreamCloseAction(section);
    action->setStream(stream);
    section->addAction(action);
    ret = streamCloseActionToScriptValue(engine, action);
    SCRIPT_EX_GUARD_END_FUN(ret)
    return ret;
}

/*^jsdoc
 * Queue the seeking of a previously opened stream, relative to its last read 
 * position
 * 
 * @method streamSeek
 * @param {ng.tx.TxStream} stream
 * @param {Number} count
 * @memberof ng.tx.TxSection
 * @returns {ng.tx.StreamSeekAction}
 * @instance
 ^jsdoc*/
static QScriptValue txSectionStreamSeek(QScriptContext *context,
                                        QScriptEngine *engine) {
    QScriptValue _this = context->thisObject();
    TxSection *section;
    txSectionFromScriptValue(_this, section);
    QScriptValue ret;
    if (context->argumentCount() < 2) {
        SCRIPT_THROW_FUN("Missing required parameter")
        return ret;
    }
    QScriptValue _stream = context->argument(0);
    TxStream *stream;
    QScriptValue count = context->argument(1);
    if (!_stream.isQObject() ||
        (stream = qobject_cast<TxStream *>(_stream.toQObject())) == 0 ||
        !count.isNumber()) {
        SCRIPT_THROW_FUN("Parameter has invalid type")
        return ret;
    }
    SCRIPT_EX_GUARD_START_FUN
    StreamSeekAction *action = new StreamSeekAction(section);
    action->setStream(stream);
    action->setCount((qint64)count.toInteger());
    section->addAction(action);
    ret = streamSeekActionToScriptValue(engine, action);
    SCRIPT_EX_GUARD_END_FUN(ret)
    return ret;
}

/*^jsdoc
 * Write from a stream to a file
 * 
 * @method writeStream
 * @param {ng.tx.TxStream} stream
 * @param {string} dest
 * @param {Number} [count=0]
 * @memberof ng.tx.TxSection
 * @returns {ng.tx.WriteStreamAction}
 * @instance
 ^jsdoc*/
static QScriptValue txSectionWriteStream(QScriptContext *context,
                                         QScriptEngine *engine) {
    QScriptValue _this = context->thisObject();
    TxSection *section;
    txSectionFromScriptValue(_this, section);
    QScriptValue ret;
    if (context->argumentCount() < 2) {
        SCRIPT_THROW_FUN("Missing required parameter")
        return ret;
    }
    QScriptValue _stream = context->argument(0);
    TxStream *stream;
    QScriptValue dest = context->argument(1);
    if (!_stream.isQObject() ||
        (stream = qobject_cast<TxStream *>(_stream.toQObject())) == 0 ||
        !dest.isString()) {
        SCRIPT_THROW_FUN("Parameter has invalid type")
        return ret;
    }
    SCRIPT_EX_GUARD_START_FUN
    WriteStreamAction *action = new WriteStreamAction(section);
    action->setStream(stream);
    action->setDest(dest.toString());
    if (context->argumentCount() >= 3) {
        QScriptValue count = context->argument(2);
        if (count.isNumber()) {
            action->setCount((qint64)count.toInteger());
        }
    }
    section->addAction(action);
    ret = writeStreamActionToScriptValue(engine, action);
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
    qScriptRegisterMetaType(engine, streamOpenActionToScriptValue,
                            streamOpenActionFromScriptValue);
    qScriptRegisterMetaType(engine, streamCloseActionToScriptValue,
                            streamCloseActionFromScriptValue);
    qScriptRegisterMetaType(engine, streamSeekActionToScriptValue,
                            streamSeekActionFromScriptValue);
    qScriptRegisterMetaType(engine, writeStreamActionToScriptValue,
                            writeStreamActionFromScriptValue);
    qScriptRegisterMetaType(engine, buildMpkActionToScriptValue,
                            buildMpkActionFromScriptValue);
    qScriptRegisterMetaType(engine, txStreamToScriptValue,
                            txStreamFromScriptValue);
    qScriptRegisterMetaType(engine, txFileStreamToScriptValue,
                            txFileStreamFromScriptValue);
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