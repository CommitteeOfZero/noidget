#pragma once

#include <QObject>
#include <QScriptable>

namespace api {

class ApiHost;

class ViewHost : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit ViewHost(ApiHost* parent);
    ~ViewHost();
};
}  // namespace api