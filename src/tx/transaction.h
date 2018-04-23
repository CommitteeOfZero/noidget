#pragma once

#include <QObject>
#include <QScriptable>
#include <QVector>
#include <QTemporaryFile>
#include "installerapplication.h"

class TxSection;

/*^jsdoc
 * Recursive sequence of steps to perform after configuration. **Not actually
 * transactional** (yet).
 *
 * The global {@link ng.fs.Fs} instance is used for all path handling.
 *
 * At the top level, transactions are divided into {@link ng.tx.TxSection}s
 * which are executed in order. The name of the current section is displayed on
 * the progress page.
 *
 * @class Transaction
 * @memberof ng.tx
 * @toplevel
 * @hideconstructor
 ^jsdoc*/
class Transaction : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit Transaction(QObject* parent);
    ~Transaction();

    Q_INVOKABLE TxSection* addSection(const QString& title);
    Q_INVOKABLE void addExecuteAfterFinish(const QString& cmd);

    qint64 prepare();  // returns size
    void run();
    void runPost();

    bool isStarted() { return _isStarted; }
    bool isCancelled() { return _isCancelled; }

    int sectionCount() { return _sections.count(); }

    QString logFileName();

   signals:
    void sectionChanged(int i, const QString& title);
    void log(const QString& text);
    void progress(qint64 progress);
    void cancelled();

   public slots:
    void handleAppStateChange(InstallerApplication::State newState);

   private slots:
    void sectionLog(const QString& text, bool fileOnly = false);

   private:
    QVector<TxSection*> _sections;
    QVector<qint64> _sectionSizes;
    QVector<QString> _postFinishCmds;
    QTemporaryFile* _logFile = nullptr;
    qint64 _roughProgress = 0;
    bool _isPrepared = false;
    bool _isStarted = false;
    bool _isCancelled = false;

    void logToFile(const QString& text);
};