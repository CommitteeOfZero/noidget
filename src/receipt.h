#pragma once

#include <QObject>
#include <QSet>
#include <QString>
#include <QFile>
#include <QDataStream>
#include "win32_registry.h"

struct RegKeyRecord {
    Registry::RootKey root;
    QString key;
    bool use64bit;
    bool operator==(const RegKeyRecord& other) const {
        return root == other.root && key == other.key &&
               use64bit == other.use64bit;
    }
};
struct RegValRecord {
    Registry::RootKey root;
    QString key;
    bool use64bit;
    QString valName;
    bool operator==(const RegValRecord& other) const {
        return root == other.root && key == other.key &&
               use64bit == other.use64bit && valName == other.valName;
    }
};
// I don't know what I'm doing help
// https://stackoverflow.com/a/22402626
inline uint qHash(const RegKeyRecord& record, uint seed = 0) {
    return qHash((int)record.root) ^ qHash(record.key) + qHash(record.use64bit);
}
inline uint qHash(const RegValRecord& record, uint seed = 0) {
    return qHash((int)record.root) ^
           qHash(record.key) + qHash(record.use64bit) + qHash(record.valName);
}
inline uint qHash(const QSet<RegKeyRecord>& set, uint seed = 0) {
    return std::accumulate(set.begin(), set.end(), seed,
                           [](uint seed, const RegKeyRecord& value) {
                               return seed + qHash(value);  // or ^
                           });
}
inline uint qHash(const QSet<RegValRecord>& set, uint seed = 0) {
    return std::accumulate(set.begin(), set.end(), seed,
                           [](uint seed, const RegValRecord& value) {
                               return seed + qHash(value);  // or ^
                           });
}

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
    void logRegKeyCreate(Registry::RootKey root, const QString& key,
                         bool use64bit);
    void logRegValueCreate(Registry::RootKey root, const QString& key,
                           bool use64bit, const QString& valName);

   private:
    const qint32 FileFormatVersion = 1;
    enum class TokenType { File = 0, RegKey = 1, RegValue = 2 };

    struct Store {
        qint32 version;
        QSet<QString> filesCreated;
        QSet<RegKeyRecord> regKeysCreated;
        QSet<RegValRecord> regValsCreated;
    };

    Store _store;
    bool _isLogging = false;

    QDataStream _out;
    QFile* _outFile = nullptr;

    Store loadOldLog(const QString& path);

    void writeLogFileCreate(const QString& path);
    void writeLogRegKeyCreate(const RegKeyRecord& record);
    void writeLogRegValueCreate(const RegValRecord& record);
};