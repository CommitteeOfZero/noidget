#pragma once

#include <QObject>
#include <QVector>
#include <QJSValue>
#include <QVariant>
#include "win32_registry.h"

class TxAction;
class TxStream;
class CopyFilesAction;
class LogAction;
class CreateDirectoryAction;
class StreamOpenAction;
class StreamCloseAction;
class StreamSeekAction;
class WriteStreamAction;
class BuildMpkAction;
class BinarySearchReplaceAction;
#ifdef Q_OS_WIN32
class SetRegistryValueAction;
#endif
class CreateShortcutAction;
class RemoveDirectoryAction;
class RollbackReceiptAction;
class RemoveFileAction;

/*^jsdoc
 * Subsequence of steps in a transaction (purely for organisational purposes)
 *
 * @class TxSection
 * @memberof ng.tx
 * @static
 * @toplevel
 * @hideconstructor
 * @property {string} title - Section heading displayed in log and on progress page
 ^jsdoc*/
class TxSection : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)

   public:
    explicit TxSection(QObject* parent);
    ~TxSection();

    QString title() { return _title; }
    void setTitle(const QString& title) { _title = title; }

    void addAction(TxAction* action);
    qint64 size();
    qint64 subactionCount();
    void prepare();
    void run();

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
    Q_INVOKABLE CopyFilesAction* copyFiles(const QString& src,
                                           const QString& dest);
    /*^jsdoc
     * Write plain text to the log during section
     *
     * @method log
     * @param {string} text
     * @param {boolean} [fileOnly=false]
     * @memberof ng.tx.TxSection
     * @returns {ng.tx.LogAction}
     * @instance
     ^jsdoc*/
    Q_INVOKABLE LogAction* log(const QString& text, bool fileOnly = false);
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
    Q_INVOKABLE CreateDirectoryAction* createDirectory(const QString& path);
    /*^jsdoc
     * Queue the opening of a stream
     *
     * @method streamOpen
     * @param {ng.tx.TxStream} stream
     * @memberof ng.tx.TxSection
     * @returns {ng.tx.StreamOpenAction}
     * @instance
     ^jsdoc*/
    Q_INVOKABLE StreamOpenAction* streamOpen(TxStream* stream);
    /*^jsdoc
     * Queue the closing of a previously opened stream
     *
     * @method streamClose
     * @param {ng.tx.TxStream} stream
     * @memberof ng.tx.TxSection
     * @returns {ng.tx.StreamCloseAction}
     * @instance
     ^jsdoc*/
    Q_INVOKABLE StreamCloseAction* streamClose(TxStream* stream);
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
    Q_INVOKABLE StreamSeekAction* streamSeek(TxStream* stream, qint64 count);
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
    Q_INVOKABLE WriteStreamAction* writeStream(TxStream* stream,
                                               const QString& dest,
                                               qint64 count = 0);
    /*^jsdoc
     * Build an MPK archive
     *
     * @method buildMpk
     * @param {string} path
     * @memberof ng.tx.TxSection
     * @returns {ng.tx.BuildMpkAction}
     * @instance
     ^jsdoc*/
    Q_INVOKABLE BuildMpkAction* buildMpk(const QString& path);
    /*^jsdoc
     * Search and replace a pattern in a binary file
     *
     * @method binarySearchReplace
     * @param {string} path
     * @param {string} needle
     * @param {string} replace
     * @memberof ng.tx.TxSection
     * @returns {ng.tx.BinarySearchReplaceAction}
     * @instance
     ^jsdoc*/
    Q_INVOKABLE BinarySearchReplaceAction* binarySearchReplace(
        const QString& path, const QString& needle, const QString& replace);
#ifdef Q_OS_WIN32
    /*^jsdoc
     * Set a registry value (Win32 only)
     *
     * @method setRegistryValue
     * @param {ng.win32.RootKey} root
     * @param {string} key
     * @param {boolean} use64bit - request 64-bit (`true`) or 32-bit (`false`) registry view on 64-bit Windows
     * @param {string} valName
     * @param value - string or number (converted to unsigned 32-bit integer REG_DWORD)
     * @memberof ng.tx.TxSection
     * @returns {ng.tx.SetRegistryValueAction}
     * @instance
     ^jsdoc*/
    Q_INVOKABLE SetRegistryValueAction* setRegistryValue(
        Registry::RootKey root, const QString& key, bool use64bit,
        const QString& valName, const QVariant& value);
#endif
    /*^jsdoc
     * Create a (desktop/start menu) shortcut (Win32, Linux only)
     *
     * @method createShortcut
     * @param {Object} params
     * @param {string} params.shortcutPath **(Required)** File path of the shortcut itself
     * @param {string} params.version Linux only. Display version
     * @param {string} params.displayName Linux only. Display name - on Windows, that's just the shortcut's filename itself minus .lnk.
     * @param {string} params.targetPath **(Required)** File path to the shortcut's target
     * @param {string} params.targetArgs Command-line arguments (if any). Note these are *not* parsed for FS macros.
     * @param {string} params.workingDir Working directory to execute the target in (or default)
     * @param {string} params.iconPath (Persistent) path to the icon to use (or default). On Windows, always uses the first icon present in that file.
     * @param {string} params.tooltip Display description
     * @param {string} params.xdgCategories Linux only. Semicolon-separated list of [XDG menu entry categories]{@link https://standards.freedesktop.org/menu-spec/latest/apa.html}
     * @memberof ng.tx.TxSection
     * @returns {ng.tx.CreateShortcutAction}
     * @instance
     ^jsdoc*/
    Q_INVOKABLE CreateShortcutAction* createShortcut(const QJSValue& params);
    /*^jsdoc
     * Remove directory operation (recursive)
     *
     * @method removeDirectory
     * @param {string} path
     * @param {bool} [onlyIfEmpty=false]
     * @memberof ng.tx.TxSection
     * @returns {ng.tx.RemoveDirectoryAction}
     * @instance
     ^jsdoc*/
    Q_INVOKABLE RemoveDirectoryAction* removeDirectory(
        const QString& path, bool onlyIfEmpty = false);
    /*^jsdoc
     * Main uninstall operation
     *
     * May only be used in uninstall mode
     *
     * @method rollbackReceipt
     * @memberof ng.tx.TxSection
     * @returns {ng.tx.RollbackReceiptAction}
     * @instance
     ^jsdoc*/
    Q_INVOKABLE RollbackReceiptAction* rollbackReceipt();
    /*^jsdoc
     * Remove single file operation
     *
     * @method removeFile
     * @param {string} path
     * @memberof ng.tx.TxSection
     * @returns {ng.tx.RemoveFileAction}
     * @instance
     ^jsdoc*/
    Q_INVOKABLE RemoveFileAction* removeFile(const QString& path);

   signals:
    void actionLogged(const QString& text, bool fileOnly = false);
    void progress(qint64 progress);
    void subactionProgress(qint64 progress);
    void cancelled();

   public slots:
    void cancel() {
        _isCancelled = true;
        emit cancelled();
    }

   private slots:
    void actionLog(const QString& text, bool fileOnly = false);

   private:
    QVector<TxAction*> _actions;
    QVector<qint64> _actionSizes;
    QVector<qint64> _actionSubactionCounts;
    QString _title;
    qint64 _roughProgress = 0;
    qint64 _roughSubactionProgress = 0;
    bool _isCancelled = false;
};
