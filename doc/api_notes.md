- Type names need to be fully qualified in `Q_INVOKABLE`, `Q_PROPERTY` function signatures, see https://wiki.qt.io/How_to_use_a_C_class_declared_in_a_namespace_with_Q_PROPERTY_and_QML and https://bugreports.qt.io/browse/QTBUG-15459
- C++ exceptions are not passed to the scripting engine. Use macros defined in `api/exception.h` to throw exceptions into JS land or catch and rethrow exceptions from other functions. Naturally, `context()->throwError()` does not unwind the C++-side callstack.
- `context()` is only set when a function is called *directly* from JS.
   ```c++
   bool bar() {
       qDebug() << context() == nullptr;
   }
   Q_INVOKABLE bool foo() {
       bar();
   }

   engine->evaluate("foo()"); # => true
   ```