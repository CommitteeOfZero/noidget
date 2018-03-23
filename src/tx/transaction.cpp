#include "transaction.h"
#include "txsection.h"
#include "installerapplication.h"
#include "fs.h"
#include <util/exception.h>
#include <QProcess>

Transaction::Transaction(QObject* parent = 0) : QObject(parent) {}
Transaction::~Transaction() {}

TxSection* Transaction::addSection(const QString& title) {
    TxSection* section = new TxSection(this);
    section->setTitle(title);
    connect(section, &TxSection::log, this, &Transaction::sectionLog);
    _sections.append(section);
    return section;
}

void Transaction::addExecuteAfterFinish(const QString& cmd) {
    _postFinishCmds.append(cmd);
}

// call this before run()
qint64 Transaction::prepare() {
    if (_isPrepared) {
        throw NgException("Tried to prepare transaction twice");
    }
    qint64 size = 0;
    for (TxSection* section : _sections) {
        section->prepare();
        size += section->size();
    }
    _isPrepared = true;
    return size;
}

void Transaction::run() {
    if (!_isPrepared) {
        throw NgException("Tried to run transaction before preparing it");
    }
    for (int i = 0; i < _sections.count(); i++) {
        TxSection* section = _sections[i];
        emit sectionChanged(i, section->title());
        section->run();
    }
}

// TODO wait for process to finish, set working directory
void Transaction::runPost() {
    for (const QString& cmd : _postFinishCmds) {
        QString expandedCmd = ngApp->globalFs()->expandedPath(cmd);
        QProcess::startDetached(cmd);
    }
}