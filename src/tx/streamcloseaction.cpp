#include "streamcloseaction.h"

void StreamCloseAction::run() { _stream->close(); }