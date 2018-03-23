#pragma once

#include <QObject>
#include <QScriptable>

class TxAction : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit TxAction(QObject* parent = 0) : QObject(parent) {}
    virtual ~TxAction() {}
    virtual void run() = 0;

    qint64 size() { return _sizeOverridden ? _sizeOverride : calcSize(); }
    Q_INVOKABLE void overrideSize(qint64 newSize) {
        _sizeOverridden = true;
        _sizeOverride = newSize;
    }

   signals:
    void log(const QString& text);

   protected:
    virtual qint64 calcSize() { return 0; }

   private:
    bool _sizeOverridden = false;
    qint64 _sizeOverride;
};