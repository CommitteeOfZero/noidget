#include "transaction.h"
#include "txsection.h"
#include "installerapplication.h"
#include "fs.h"
#include <util/exception.h>
#include <QProcess>

Transaction::Transaction(QObject* parent = 0) : QObject(parent) {}
Transaction::~Transaction() {}

/*^jsdoc
 * Append a section
 * 
 * @method addSection
 * @param {string} title
 * @memberof ng.tx.Transaction
 * @returns {ng.tx.TxSection}
 * @instance
 ^jsdoc*/
TxSection* Transaction::addSection(const QString& title) {
    TxSection* section = new TxSection(this);
    section->setTitle(title);
    connect(section, &TxSection::log, this, &Transaction::sectionLog);
    _sections.append(section);
    int i = _sections.count() - 1;
    connect(section, &TxSection::progress, [i, this](qint64 sectionProgress) {
        sectionProgress = qMin(_sectionSizes[i], sectionProgress);
        emit progress(_roughProgress + sectionProgress);
    });
    return section;
}

/*^jsdoc
 * Add a command to run when the installer closes
 * 
 * Commands are started in the order they are added, but without waiting for each
 * other to exit.
 * 
 * @method addExecuteAfterFinish
 * @param {string} cmd
 * @memberof ng.tx.Transaction
 * @instance
 ^jsdoc*/
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
        qint64 sectionSize = section->size();
        _sectionSizes.append(sectionSize);
        size += sectionSize;
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
        _roughProgress += _sectionSizes[i];
        emit progress(_roughProgress);
    }
}

// TODO wait for process to finish, set working directory
void Transaction::runPost() {
    for (const QString& cmd : _postFinishCmds) {
        QString expandedCmd = ngApp->globalFs()->expandedPath(cmd);
        QProcess::startDetached(cmd);
    }
}

void Transaction::sectionLog(const QString& text) { emit log(text); }