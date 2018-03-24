#include "copyfilesaction.h"
#include "installerapplication.h"
#include "fs.h"
#include <util/exception.h>
#include <QDir>
#include <QDirIterator>

CopyFilesAction::CopyFilesAction(QObject* parent = 0) : TxAction(parent) {
    _fs = ngApp->globalFs();
}

void CopyFilesAction::prepare() {
    if (_src.endsWith('*')) {
        QString srcDir = _src.left(_src.length() - 1);
        if (!_fs->pathIsDirectory(srcDir)) {
            throw NgException(
                QString("Tried to copy files from unreadable directory: %1")
                    .arg(srcDir));
        }
        QDirIterator it(_fs->expandedPath(srcDir),
                        QDir::AllEntries | QDir::Hidden | QDir::System |
                            QDir::NoDotAndDotDot);
        while (it.hasNext()) {
            _srcPaths.append(it.next());
        }
    } else {
        QString srcPath = _fs->expandedPath(_src);
        if (!_fs->pathIsReadable(srcPath)) {
            throw NgException(
                QString("Tried to copy files from unreadable path: %1")
                    .arg(srcPath));
        }
        _srcPaths.append(srcPath);
    }
}

qint64 CopyFilesAction::calcSize() {
    qint64 result = 0;
    for (QString path : _srcPaths) {
        if (_fs->pathIsFile(path)) {
            result += QFileInfo(path).size();
        } else {
            QDirIterator it(
                path,
                QDir::AllEntries | QDir::Hidden | QDir::System |
                    QDir::NoDotAndDotDot,
                QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);
            while (it.hasNext()) {
                QString entryPath = it.next();
                if (_fs->pathIsFile(entryPath)) {
                    result += QFileInfo(entryPath).size();
                }
            }
        }
    }
    return result;
}

void CopyFilesAction::copySingleFile(const QString& src, const QString& dest) {
    emit log(dest);

    QFile in(src);
    if (!in.open(QIODevice::ReadOnly)) {
        throw NgException(QString("Could not read file: %1").arg(src));
    }
    QFile out(dest);
    if (!out.open(QIODevice::WriteOnly)) {
        throw NgException(QString("Could not write file: %1").arg(dest));
    }

    void* buffer = malloc(1024 * 1024);
    qint64 bytesRead = 0;
    while ((bytesRead = in.read((char*)buffer, 1024 * 1024)) > 0) {
        if (_isCancelled) {
            emit log(QString("File copy to %1 aborted mid-write after user "
                             "cancelled transaction")
                         .arg(dest));
            return;
        }
        out.write((const char*)buffer, bytesRead);
        _progress += bytesRead;
        emit progress(_progress);
    }
}

// TODO symlink handling?
void CopyFilesAction::run() {
    QString expandedSrc = _fs->expandedPath(_src);
    QString expandedDest = _fs->expandedPath(_dest);

    emit log(QString("Copying %1 to %2...").arg(expandedSrc, expandedDest));

    if (_fs->pathIsFile(expandedSrc)) {
        // copy single file
        // TODO check if these endsWith()s make sense with expandedPath()s
        if (expandedDest.endsWith('/') || expandedDest.endsWith('\\') ||
            _fs->pathIsDirectory(expandedDest)) {
            // to a directory
            _fs->createDirectory(expandedDest);
            QString destFile =
                QDir(expandedDest)
                    .absoluteFilePath(QFile(expandedSrc).fileName());
            copySingleFile(expandedSrc, destFile);
        } else {
            // to a (named) file
            _fs->createDirectory(QFileInfo(expandedDest).dir().absolutePath());
            copySingleFile(expandedSrc, expandedDest);
        }
    } else {
        _fs->createDirectory(expandedDest);
        QDir src(expandedSrc), dest(expandedDest);

        for (QString path : _srcPaths) {
            if (_isCancelled) {
                return;
            }
            if (_fs->pathIsFile(path)) {
                QString relativeSrc = src.relativeFilePath(path);
                QString absoluteDest = dest.absoluteFilePath(relativeSrc);
                copySingleFile(path, absoluteDest);
            } else {
                QDirIterator it(path,
                                QDir::AllEntries | QDir::Hidden | QDir::System |
                                    QDir::NoDotAndDotDot,
                                QDirIterator::Subdirectories |
                                    QDirIterator::FollowSymlinks);
                while (it.hasNext()) {
                    if (_isCancelled) {
                        return;
                    }
                    QString entryPath = it.next();
                    QString entryDest =
                        dest.absoluteFilePath(src.relativeFilePath(entryPath));
                    if (_fs->pathIsDirectory(entryPath)) {
                        _fs->createDirectory(entryDest);
                    } else {
                        _fs->createDirectory(
                            QFileInfo(entryDest).dir().absolutePath());
                        copySingleFile(entryPath, entryDest);
                    }
                }
            }
        }
    }
}