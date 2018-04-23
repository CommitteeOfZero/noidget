#include "transaction.h"
#include "txsection.h"
#include "fs.h"
#include <util/exception.h>
#include <QProcess>
#include <QDir>
#include <QTextStream>
#include <QDateTime>

Transaction::Transaction(QObject* parent = 0) : QObject(parent) {
    connect(ngApp, &InstallerApplication::currentStateChanged, this,
            &Transaction::handleAppStateChange);
}
Transaction::~Transaction() {
    if (_logFile != nullptr) {
        delete _logFile;
        _logFile = nullptr;
    }
}

QString Transaction::logFileName() {
    if (_logFile == nullptr) return QString();
    return _logFile->fileName();
}

void Transaction::handleAppStateChange(InstallerApplication::State newState) {
    if (newState == InstallerApplication::State::Cancelled) {
        _isCancelled = true;
        logToFile("User cancelled transaction.");
        emit cancelled();
    }
}

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
    connect(this, &Transaction::cancelled, section, &TxSection::cancel);
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

    _logFile = new QTemporaryFile(QDir::tempPath() + "/noidget.XXXXXX.txt");
    _logFile->setAutoRemove(false);
    _logFile->open();
    _logFile->setTextModeEnabled(true);
    sectionLog(QString("Logging to %1").arg(_logFile->fileName()));

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
    if (_isStarted) {
        throw NgException("Tried to start transaction twice");
    }
    _isStarted = true;
    for (int i = 0; i < _sections.count(); i++) {
        if (_isCancelled) {
            break;
        }
        TxSection* section = _sections[i];
        emit sectionChanged(i, section->title());
        section->run();
        _roughProgress += _sectionSizes[i];
        emit progress(_roughProgress);
    }
    if (_isCancelled) {
        emit log("User cancelled transaction");
    } else {
        ngApp->setCurrentState(InstallerApplication::State::Finished);
    }
}

// TODO wait for process to finish, set working directory
void Transaction::runPost() {
    for (const QString& cmd : _postFinishCmds) {
        QString expandedCmd = ngApp->globalFs()->expandedPath(cmd);
        QProcess::startDetached(cmd);
    }
}

void Transaction::sectionLog(const QString& text, bool fileOnly) {
    if (!fileOnly) {
        emit log(text);
    }
    logToFile(text);
}

void Transaction::logToFile(const QString& text) {
    if (_logFile == nullptr || !_logFile->isOpen()) return;
    QTextStream stream(_logFile);
    QString timestamp =
        QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd HH:mm:ss");
    stream << QString("[%1 UTC] %2").arg(timestamp, text) << endl;
}