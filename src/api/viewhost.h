#pragma once

#include <QObject>
#include <QJSValue>

namespace api {

class ApiHost;

/*^jsdoc
 * @namespace view
 * @memberof ng
 * @static
 * @hidesecondlevel
 ^jsdoc*/
class ViewHost : public QObject {
    Q_OBJECT

   public:
    explicit ViewHost(ApiHost* parent);
    void setupScriptObject(QJSValue& o);
    ~ViewHost();
};
}  // namespace api
