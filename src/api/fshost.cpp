#include "fshost.h"
#include "apihost.h"
#include "fs.h"
#include "installerapplication.h"
#include <api/exception.h>

namespace api {
FsHost::FsHost(ApiHost *parent) : QObject(parent) {
    qRegisterMetaType<Fs *>("Fs*");
}
void FsHost::setupScriptObject(QJSValue &o) {}
FsHost::~FsHost() {}

/*^jsdoc
 * Creates a new {@link ng.fs.Fs}
 * @method createFs
 * @memberof ng.fs
 * @static
 * @returns {ng.fs.Fs}
 ^jsdoc*/
Fs *FsHost::createFs() {
    ENFORCE_SCRIPT
    Fs *fs = new Fs();
    QJSEngine::setObjectOwnership(fs, QJSEngine::JavaScriptOwnership);
    return fs;
}
/*^jsdoc
 * Returns a global {@link ng.fs.Fs} instance.
 *
 * Care must be taken when setting macros on this in a page, as they are not
 reset if the user goes back.
 * @method global
 * @memberof ng.fs
 * @static
 * @returns {ng.fs.Fs}
 ^jsdoc*/
Fs *FsHost::global() { return ngApp->globalFs(); }

}  // namespace api
