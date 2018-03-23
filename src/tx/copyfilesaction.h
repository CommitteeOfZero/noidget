#pragma once

#include "txaction.h"
#include <QObject>
#include <QScriptable>
#include <QVector>

class Fs;

class CopyFilesAction : public TxAction {
    Q_OBJECT
    Q_PROPERTY(QString src READ src WRITE setSrc)
    Q_PROPERTY(QString dest READ dest WRITE setDest)

   public:
    explicit CopyFilesAction(QObject* parent);
    void prepare() override;
    void run() override;

    QString src() { return _src; }
    void setSrc(const QString& src) { _src = src; }
    QString dest() { return _dest; }
    void setDest(const QString& dest) { _dest = dest; }

   private:
    QString _src, _dest;
    QVector<QString> _srcPaths;
    qint64 progress = 0;
    Fs* _fs;

    qint64 calcSize() override;
    void copySingleFile(const QString& src, const QString& dest);
};