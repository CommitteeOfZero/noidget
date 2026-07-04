#include "txhost.h"
#include "apihost.h"
#include "receiptwriter.h"
#include "tx/transaction.h"
#include "tx/txsection.h"
#include "tx/txaction.h"
#include "tx/txfilestream.h"
#include "tx/txxdelta3stream.h"
#include "tx/txmpkinputstream.h"
#include "tx/copyfilesaction.h"
#include "tx/logaction.h"
#include "tx/createdirectoryaction.h"
#include "tx/streamopenaction.h"
#include "tx/streamcloseaction.h"
#include "tx/streamseekaction.h"
#include "tx/writestreamaction.h"
#include "tx/buildmpkaction.h"
#include "tx/binarysearchreplaceaction.h"
#ifdef Q_OS_WIN32
#include "tx/setregistryvalueaction.h"
#endif
#include "tx/createshortcutaction.h"
#include "tx/removedirectoryaction.h"
#include "tx/rollbackreceiptaction.h"
#include "tx/removefileaction.h"
#include "installerapplication.h"
#include "progresspage.h"
#include "installerwindow.h"
#include <api/exception.h>

namespace api {
TxHost::TxHost(ApiHost *parent) : QObject(parent) {
    qRegisterMetaType<Transaction *>("Transaction*");
    qRegisterMetaType<TxSection *>("TxSection*");
    qRegisterMetaType<TxAction *>("TxAction*");
    qRegisterMetaType<CopyFilesAction *>("CopyFilesAction*");
    qRegisterMetaType<LogAction *>("LogAction*");
    qRegisterMetaType<CreateDirectoryAction *>("CreateDirectoryAction*");
    qRegisterMetaType<StreamOpenAction *>("StreamOpenAction*");
    qRegisterMetaType<StreamCloseAction *>("StreamCloseAction*");
    qRegisterMetaType<StreamSeekAction *>("StreamSeekAction*");
    qRegisterMetaType<WriteStreamAction *>("WriteStreamAction*");
    qRegisterMetaType<BuildMpkAction *>("BuildMpkAction*");
    qRegisterMetaType<BinarySearchReplaceAction *>("BinarySearchReplaceAction*");
#ifdef Q_OS_WIN32
    qRegisterMetaType<SetRegistryValueAction *>("SetRegistryValueAction*");
#endif
    qRegisterMetaType<CreateShortcutAction *>("CreateShortcutAction*");
    qRegisterMetaType<RemoveDirectoryAction *>("RemoveDirectoryAction*");
    qRegisterMetaType<RollbackReceiptAction *>("RollbackReceiptAction*");
    qRegisterMetaType<RemoveFileAction *>("RemoveFileAction*");
    qRegisterMetaType<TxStream *>("TxStream*");
    qRegisterMetaType<TxFileStream *>("TxFileStream*");
    qRegisterMetaType<TxXdelta3Stream *>("TxXdelta3Stream*");
    qRegisterMetaType<TxMpkInputStream *>("TxMpkInputStream*");
}
void TxHost::setupScriptObject(QJSValue &o) {}
TxHost::~TxHost() {}

/*^jsdoc
 * Prepare a stream for reading from file
 *
 * @method fileStream
 * @param {string} inPath
 * @memberof ng.tx
 * @returns {ng.tx.TxFileStream}
 * @static
 ^jsdoc*/
TxFileStream *TxHost::fileStream(const QString &inPath) {
    SCRIPT_EX_GUARD_START
    TxFileStream *ret = new TxFileStream(tx());
    ret->setInPath(inPath);
    return ret;
    SCRIPT_EX_GUARD_END(nullptr)
}

/*^jsdoc
 * Prepare a stream for decoding a VCDIFF file
 *
 * @method xdelta3Stream
 * @param {ng.tx.TxStream} srcStream
 * @param {ng.tx.TxStream} diffStream
 * @memberof ng.tx
 * @returns {ng.tx.TxXdelta3Stream}
 * @static
 ^jsdoc*/
TxXdelta3Stream *TxHost::xdelta3Stream(TxStream *srcStream,
                                       TxStream *diffStream) {
    SCRIPT_EX_GUARD_START
    TxXdelta3Stream *ret = new TxXdelta3Stream(tx());
    ret->setSrcStream(srcStream);
    ret->setDiffStream(diffStream);
    return ret;
    SCRIPT_EX_GUARD_END(nullptr)
}

/*^jsdoc
 * Prepare a stream for reading an MPK entry
 *
 * @method mpkInputStream
 * @param {string} inPath
 * @param {number} entry
 * @memberof ng.tx
 * @returns {ng.tx.TxMpkInputStream}
 * @static
 ^jsdoc*/
TxMpkInputStream *TxHost::mpkInputStream(const QString &inPath, quint32 entry) {
    SCRIPT_EX_GUARD_START
    TxMpkInputStream *ret = new TxMpkInputStream(tx());
    ret->setInPath(inPath);
    ret->setEntry(entry);
    return ret;
    SCRIPT_EX_GUARD_END(nullptr)
}

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
