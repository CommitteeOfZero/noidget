#pragma once

#include <QObject>
#include <QString>
#include <QScriptable>

namespace api {

class ApiHost;

class SystemInfo : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit SystemInfo(ApiHost* parent);
    ~SystemInfo();

    Q_INVOKABLE QString platform() const;
};
}  // namespace api