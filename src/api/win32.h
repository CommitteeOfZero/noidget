#pragma once

#include <QObject>
#include <QString>
#include <QScriptable>
#ifdef Q_OS_WIN32
#include <win32_registry.h>

namespace api {

class ApiHost;

/*^jsdoc
 * @namespace win32
 * @memberof ng
 * @static
 * @toplevel
 ^jsdoc*/
class Win32 : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit Win32(ApiHost* parent);
    void setupScriptObject(QScriptValue& o);
    ~Win32();

    Q_INVOKABLE Registry* registry() const;
};
}  // namespace api
#endif