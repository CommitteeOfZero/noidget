#pragma once

#include <QObject>
#include <QVector>
#include <QScriptable>

class TxAction;

/*^jsdoc
 * Subsequence of steps in a transaction (purely for organisational purposes)
 *
 * @class TxSection
 * @memberof ng.tx
 * @toplevel
 * @hideconstructor
 ^jsdoc*/
class TxSection : public QObject, protected QScriptable {
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)

   public:
    explicit TxSection(QObject* parent);
    ~TxSection();

    QString title() { return _title; }
    void setTitle(const QString& title) { _title = title; }

    // TODO move all of this stuff into API, add types
    /*
    Q_INVOKABLE void copyFiles(const QString& source,
                               const QString& destination);
    Q_INVOKABLE void log(const QString& text);
    Q_INVOKABLE void createDirectory(const QString& path);
    Q_INVOKABLE void buildMpk(const QString& path);
    Q_INVOKABLE void streamOpen(void* stream);
    Q_INVOKABLE void streamClose(void* stream);
    Q_INVOKABLE void streamSeek(void* stream, qint64 bytes);
    Q_INVOKABLE void streamWriter(void* stream, const QString& path);
    Q_INVOKABLE void binarySearchReplace(const QString& path,
                                         const QString& needle,
                                         const QString& replace);
    */
    void addAction(TxAction* action);
    qint64 size();
    void run();

   signals:
    void log(const QString& text);

   private slots:
    void actionLog(const QString& text);

   private:
    QVector<TxAction*> _actions;
    QString _title;
};