#pragma once

#include <QJSEngine>
#include <QJSValue>
#include <util/exception.h>

// NOTE: qjsEngine(this) returns non-null once `this` has been wrapped into
// the script engine via QJSEngine::newQObject() - either directly (the
// long-lived ng.* singletons: Window, TxHost, FsHost, view widgets after
// being returned to script, ...) or as a side effect of being returned from
// / passed as an argument to an already-wrapped object's invokable method.
// Objects that are never exposed to script (e.g. a private helper widget
// such as Dialog/Page's own Column, or a freshly-`new`'d object before it is
// handed back to script) see qjsEngine(this) == nullptr for their entire
// lifetime, which is what lets an exception raised from deep inside such a
// helper propagate as a plain C++ exception up to whichever *wrapped* object
// actually catches it and turns it into a script-visible error - mirroring
// the old QScriptable::context() based behaviour documented in
// doc/api_notes.md, just decided per-object instead of per-call-frame.

#define SCRIPT_EX_GUARD_START try {
#define SCRIPT_EX_GUARD_END(defaultReturn)                          \
    }                                                                \
    catch (const NgException& ex) {                                  \
        QJSEngine* _ngEngine = qjsEngine(this);                      \
        if (_ngEngine == nullptr) {                                   \
            throw;                                                    \
        } else {                                                      \
            _ngEngine->throwError(ex.qWhat());                        \
        }                                                              \
        return defaultReturn;                                          \
    }

#define SCRIPT_THROW(what)                          \
    if (qjsEngine(this) == nullptr) {                \
        throw NgException(what);                     \
    } else {                                         \
        qjsEngine(this)->throwError(QString(what));  \
    }

#define ENFORCE_SCRIPT                                               \
    if (qjsEngine(this) == nullptr) {                                 \
        throw NgException(                                             \
            "Tried to call script-only functions from native code");    \
    }

namespace api {

// Shows a QMessageBox for `result` if it holds an uncaught script exception
// (QJSValue::isError()), using its message + JS stack trace. Returns whether
// an error was shown. Called after every point where JS code we don't
// control the body of is invoked (the top-level script.js evaluate(), and
// every later JS callback invocation - onClick/onChange/onNext/onPick/etc.)
// since QJSEngine, unlike QtScript, has no engine-wide "uncaught exception"
// hook to catch these centrally.
bool reportIfScriptError(const QJSValue& result);

}  // namespace api
