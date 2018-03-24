#pragma once

#include <QObject>
#include <QScriptable>
#include <QVector>

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
 * @namespace tx
 * @memberof ng
 * @toplevel
 * @static
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

    int sectionCount() { return _sections.count(); }

   signals:
    void sectionChanged(int i, const QString& title);
    void log(const QString& text);
    void progress(qint64 progress);

   private slots:
    void sectionLog(const QString& text);

   private:
    QVector<TxSection*> _sections;
    QVector<qint64> _sectionSizes;
    QVector<QString> _postFinishCmds;
    qint64 _roughProgress = 0;
    bool _isPrepared = false;
};