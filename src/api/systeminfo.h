#pragma once

#include <QObject>
#include <QString>
#include <QScriptable>

namespace api {

class ApiHost;

/*^jsdoc
 * @namespace systemInfo
 * @memberof ng
 * @static
 * @toplevel
 ^jsdoc*/
class SystemInfo : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    /*^jsdoc
     * Operating system family
     * @namespace OsFamily
     * @memberof ng.systemInfo
     * @static
     * @toplevel
     * @property {number} Unknown
     * @property {number} Windows
     * @property {number} Mac
     * @property {number} Linux
     ^jsdoc*/
    enum class OsFamily { Unknown, Windows, Mac, Linux };
    Q_ENUM(OsFamily)

    explicit SystemInfo(ApiHost* parent);
    void setupScriptObject(QScriptValue& o);
    ~SystemInfo();

    Q_INVOKABLE api::SystemInfo::OsFamily platform() const;
};
}  // namespace api