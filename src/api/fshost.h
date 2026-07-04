#pragma once

#include <QObject>
#include <QJSValue>

class Fs;

namespace api {

class ApiHost;

/*^jsdoc
 * @namespace fs
 * @memberof ng
 * @static
 * @toplevel
 ^jsdoc*/
class FsHost : public QObject {
    Q_OBJECT

   public:
    explicit FsHost(ApiHost* parent);
    void setupScriptObject(QJSValue& o);
    ~FsHost();

    Q_INVOKABLE Fs* createFs();
    Q_INVOKABLE Fs* global();
};
}  // namespace api
