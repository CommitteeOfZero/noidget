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
 * @static
 * @toplevel
 * @hideconstructor
 * @property {string} title - Section heading displayed in log and on progress page
 ^jsdoc*/
class TxSection : public QObject, protected QScriptable {
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)

   public:
    explicit TxSection(QObject* parent);
    ~TxSection();

    QString title() { return _title; }
    void setTitle(const QString& title) { _title = title; }

    void addAction(TxAction* action);
    qint64 size();
    void prepare();
    void run();

   signals:
    void log(const QString& text);
    void progress(qint64 progress);

   private slots:
    void actionLog(const QString& text);

   private:
    QVector<TxAction*> _actions;
    QVector<qint64> _actionSizes;
    QString _title;
    qint64 _roughProgress = 0;
};