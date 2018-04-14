#pragma once

#include <QObject>
#include <QSet>
#include <QString>
#include <QFile>
#include <QDataStream>

class Receipt : public QObject {
    Q_OBJECT

   public:
    explicit Receipt(QObject* parent = 0) : QObject(parent) {
        _store.version = FileFormatVersion;
    };
    ~Receipt(){};

    void open(const QString& dir);
    void close();

    // Path is resolved with globalFs to an absolute path
    void logFileCreate(const QString& path);

   private:
    const qint32 FileFormatVersion = 1;
    enum class TokenType { File = 0 };
    struct Store {
        qint32 version;
        QSet<QString> filesCreated;
    };

    Store _store;
    bool _isLogging = false;

    QDataStream _out;
    QFile* _outFile = nullptr;

    Store loadOldLog(const QString& path);
};