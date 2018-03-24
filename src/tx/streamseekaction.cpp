#include "streamseekaction.h"

void StreamSeekAction::run() { _stream->seek(_count); }