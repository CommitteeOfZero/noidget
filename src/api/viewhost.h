#pragma once

#include <QObject>
#include <QScriptable>
#include <QScriptValue>

namespace api {

class ApiHost;

/*^jsdoc
 * @namespace view
 * @memberof ng
 * @static
 ^jsdoc*/
class ViewHost : public QObject, protected QScriptable {
    Q_OBJECT

   public:
    explicit ViewHost(ApiHost* parent);
    void setupScriptObject(QScriptValue& o);
    ~ViewHost();
};
}  // namespace api