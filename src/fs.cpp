#include "fs.h"
#include <api/exception.h>
#include <QFileInfo>
#include <QRegularExpression>
#include <QProcessEnvironment>
#include <QCryptographicHash>
#include <QFile>
#include <QDir>

// http://doc.qt.io/qt-5/qfileinfo.html#ntfs-permissions
extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;

Fs::Fs(QObject* parent) : QObject(parent), macros() {}
Fs::~Fs() {}

/*^jsdoc
 * Adds or changes macro `key` to mean `value`. Throws if `key` contains illegal
 characters.
 *
 * Valid characters are word characters and parentheses.
 * @method setMacro
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} key
 * @param {string} value
 ^jsdoc*/
void Fs::setMacro(const QString& key, const QString& value) {
    const static QRegularExpression validMacro(
        "^[\\w\\(\\)]+$", QRegularExpression::OptimizeOnFirstUsageOption);
    if (!validMacro.match(key).hasMatch()) {
        SCRIPT_THROW("Macro name contains invalid characters")
        return;
    }
    macros[key] = value;
}
/*^jsdoc
 * Removes macro `key`. Environment variables cannot be removed.
 * @method removeMacro
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} key
 ^jsdoc*/
void Fs::removeMacro(const QString& key) { macros.remove(key); }
/*^jsdoc
 * Removes all macros
 * @method clearMacros
 * @memberof ng.fs.Fs
 * @instance
 ^jsdoc*/
void Fs::clearMacros() { macros.clear(); }

/*^jsdoc
 * Expands macros in `inPath`
 * @method expandedPath
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} inPath
 * @returns {string}
 ^jsdoc*/
QString Fs::expandedPath(const QString& inPath) const {
    const static QRegularExpression matchMacro(
        "%([\\w\\(\\)]+)%", QRegularExpression::OptimizeOnFirstUsageOption);
    QString result = inPath;
    bool found;
    do {
        found = false;
        auto match = matchMacro.match(inPath);
        if (match.hasMatch()) {
            auto key = match.captured(1);
            QString replacement;
            if (macros.contains(key)) {
                found = true;
                replacement = macros[key];
            } else if (QProcessEnvironment::systemEnvironment().contains(key)) {
                found = true;
                replacement =
                    QProcessEnvironment::systemEnvironment().value(key);
            }

            if (found) {
                result.replace(match.capturedStart(1), match.capturedLength(1),
                               replacement);
            }
        }
    } while (found);
    return result;
}
/*^jsdoc
 * Expands macros in `inPath` and turns it absolute (according to the process
 working directory) if it isn't already
 * @method absPath
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} inPath
 * @returns {string}
 ^jsdoc*/
QString Fs::absPath(const QString& inPath) const {
    return QFileInfo(expandedPath(inPath)).absoluteFilePath();
}
/*^jsdoc
 * Does `path` point to an existing file or directory?
 * @method pathExists
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} path
 * @returns {boolean}
 ^jsdoc*/
bool Fs::pathExists(const QString& path) const {
    return QFileInfo::exists(expandedPath(path));
}
/*^jsdoc
 * Does `path` point to an existing directory?
 * @method pathIsDirectory
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} path
 * @returns {boolean}
 ^jsdoc*/
bool Fs::pathIsDirectory(const QString& path) const {
    return QFileInfo(expandedPath(path)).isDir();
}
/*^jsdoc
 * Does `path` point to an existing file?
 * @method pathIsFile
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} path
 * @returns {boolean}
 ^jsdoc*/
bool Fs::pathIsFile(const QString& path) const {
    return QFileInfo(expandedPath(path)).isFile();
}
/*^jsdoc
 * Does `path` point to an existing file or directory that we can read?
 * @method pathIsReadable
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} path
 * @returns {boolean}
 ^jsdoc*/
bool Fs::pathIsReadable(const QString& path) const {
    qt_ntfs_permission_lookup++;
    bool result = QFileInfo(expandedPath(path)).isReadable();
    qt_ntfs_permission_lookup--;
    return result;
}
/*^jsdoc
 * Does `path` point to an existing file or directory that we can write?
 * @method pathIsWritable
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} path
 * @returns {boolean}
 ^jsdoc*/
bool Fs::pathIsWritable(const QString& path) const {
    qt_ntfs_permission_lookup++;
    bool result = QFileInfo(expandedPath(path)).isWritable();
    qt_ntfs_permission_lookup--;
    return result;
}

/*^jsdoc
 * Computes the MD5 hash of data in `filePath`. Throws if file does not exist /
 is not readable.
 * @method md5sum
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} filePath
 * @returns {string} Hash as lowercase hexadecimal string
 ^jsdoc*/
QString Fs::md5sum(const QString& filePath) const {
    QFile f(expandedPath(filePath));
    if (!f.open(QIODevice::ReadOnly)) {
        SCRIPT_THROW("Can't open file")
        return "";
    }
    QCryptographicHash hash(QCryptographicHash::Md5);
    if (!hash.addData(&f)) {
        SCRIPT_THROW("Can't read data")
        return "";
    }

    return QString(hash.result().toHex());  // toHex() is lowercase
}

/*^jsdoc
 * Tries to rename file/directory `from` to `to`. Throws if rename operation
 fails for some reason.
 * @method rename
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} from
 * @param {string} to
 ^jsdoc*/
void Fs::rename(const QString& from, const QString& to) const {
    bool ok = QFile::rename(expandedPath(from), expandedPath(to));
    if (!ok) SCRIPT_THROW("Renaming failed");
}
/*^jsdoc
 * Tries to create directory `path`. Throws if create operation
 fails for some reason - does *not* throw if directory already exists.
 * @method createDirectory
 * @memberof ng.fs.Fs
 * @instance
 * @param {string} path
 ^jsdoc*/
void Fs::createDirectory(const QString& path) const {
    bool ok = QDir(expandedPath(path)).mkpath(".");
    if (!ok) SCRIPT_THROW("Directory creation failed");
}