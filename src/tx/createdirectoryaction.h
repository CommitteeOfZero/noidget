#pragma once

#include "txaction.h"
#include <QObject>
#include <QScriptable>

class CreateDirectoryAction : public TxAction {
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath)

   public:
    explicit CreateDirectoryAction(QObject* parent = 0) : TxAction(parent) {}
    void run() override;

    QString path() { return _path; }
    void setPath(const QString& path) { _path = path; }

   private:
    QString _path;
};