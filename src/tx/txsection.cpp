#include "txsection.h"
#include "txaction.h"

TxSection::TxSection(QObject* parent = 0) : QObject(parent) {}
TxSection::~TxSection() {}

void TxSection::addAction(TxAction* action) {
    action->setParent(this);
    connect(action, &TxAction::log, this, &TxSection::actionLog);
    _actions.append(action);
}

qint64 TxSection::size() {
    qint64 result = 0;
    for (TxAction* action : _actions) {
        result += action->size();
    }
    return result;
}

void TxSection::prepare() {
    for (TxAction* action : _actions) {
        action->prepare();
    }
}

void TxSection::run() {
    for (TxAction* action : _actions) {
        action->run();
    }
}