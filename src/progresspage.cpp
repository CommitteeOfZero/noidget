#include "progresspage.h"
#include <kofuna/invertprogressbar.h>
#include "installerapplication.h"
#include <tx/transaction.h>
#include <QFuture>
#include <QtConcurrent>
#include <QScrollBar>

ProgressPage::ProgressPage(QWidget* parent) : view::Page(parent) {
    _layout = new QVBoxLayout(this);
    _layout->setMargin(0);
    _layout->setSpacing(8);
    _layout->setAlignment(Qt::AlignTop);
    setLayout(_layout);

    _titleLbl = new QLabel(this);
    _titleLbl->setTextFormat(Qt::PlainText);
    _titleLbl->setWordWrap(false);
    _titleLbl->setText("Preparing");
    _titleLbl->setObjectName("pageHeading");
    _layout->addWidget(_titleLbl);

    _progressBar = new InvertProgressBar(this);
    _layout->addWidget(_progressBar);

    _logBox = new QTextEdit(this);
    _logBox->setReadOnly(true);
    _logBox->setAcceptRichText(false);
    _logBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    _logBox->setObjectName("logBox");
    _layout->addWidget(_logBox);

    Transaction* tx = ngApp->tx();
    connect(tx, &Transaction::sectionChanged, this,
            &ProgressPage::txSectionChange);
    connect(tx, &Transaction::log, this, &ProgressPage::getLog);
    connect(tx, &Transaction::progress, this, &ProgressPage::updateProgressBar);

    QFuture<qint64> txSize = QtConcurrent::run(tx, &Transaction::prepare);
    QFutureWatcher<void>* txSizeWatcher = new QFutureWatcher<void>(this);
    connect(txSizeWatcher, &QFutureWatcher<void>::finished, [=]() {
        qint64 rawSize = txSize.result();
        if (rawSize > INT_MAX) {
            _needProgressDownscale = true;
            _progressDownscaleFactor = (double)INT_MAX / (double)rawSize;
            _progressBar->setMaximum(INT_MAX);
        } else {
            _progressBar->setMaximum((int)rawSize);
        }

        startTx();
    });
    txSizeWatcher->setFuture(txSize);
}

void ProgressPage::attached() {
    emit nextEnabled(false);
    emit backEnabled(false);
}

void ProgressPage::startTx() {
    _sectionCount = ngApp->tx()->sectionCount();

    QFuture<void> f = QtConcurrent::run(ngApp->tx(), &Transaction::run);
    QFutureWatcher<void>* w = new QFutureWatcher<void>(this);
    connect(w, &QFutureWatcher<void>::finished, [&]() {
        // TODO do something
    });
    w->setFuture(f);
}

void ProgressPage::txSectionChange(int i, const QString& sectionTitle) {
    _titleLbl->setText(
        QString("(%1/%2) %3").arg(i + 1).arg(_sectionCount).arg(sectionTitle));
}

void ProgressPage::getLog(const QString& text) {
    _logBox->insertPlainText("\n" + text);
    // autoscroll
    _logBox->verticalScrollBar()->setValue(
        _logBox->verticalScrollBar()->maximum());
}

void ProgressPage::updateProgressBar(qint64 progress) {
    if (_needProgressDownscale) {
        _progressBar->setValue(
            (int)((double)progress * _progressDownscaleFactor));
    } else {
        _progressBar->setValue((int)progress);
    }
}
