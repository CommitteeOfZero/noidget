#include "exception.h"
#include <QMessageBox>
#include "installerapplication.h"
#include "installerwindow.h"

namespace api {

bool reportIfScriptError(const QJSValue& result) {
    if (!result.isError()) return false;

    QMessageBox mb(ngApp->window());
    mb.setText(
        QString("Script error (please send this to patch developers):\n%1")
            .arg(result.toString()));
    mb.setDetailedText(result.property("stack").toString());
    mb.setWindowTitle("Script error");
    mb.exec();
    return true;
}

}  // namespace api
