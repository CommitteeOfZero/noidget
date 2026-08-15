#include "directorypicker.h"
#include <QHBoxLayout>
#include "installerapplication.h"
#include <api/exception.h>

namespace api {
namespace view {

DirectoryPicker::DirectoryPicker(QWidget *parent) : QWidget(parent) {
    // TODO figure out how to give textbox minimum width, allow textbox *and*
    // label to expand, ensure there's enough vertical room for multiline labels
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);
    layout->setAlignment(Qt::AlignLeft);
    setLayout(layout);
    _lbl = new QLabel(this);
    _lbl->setWordWrap(true);
    _lbl->setTextFormat(Qt::PlainText);
    // When label is blank (default), we want the textbox to reach the left
    // edge, so we only make it visible (and add non-zero spacing) when it's not
    // blank
    _lbl->setVisible(false);
    _lblSpacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    layout->addWidget(_lbl);
    layout->addSpacerItem(_lblSpacer);
    _edit = new QLineEdit(this);
    layout->addWidget(_edit);
    _btn = new QPushButton(this);
    _btn->setText("Browse...");
    layout->addWidget(_btn);

    // TODO do this cleanly
    _edit->setFixedHeight(_btn->height() - 4);

    // no parent - avoid styling
    _dlg = new QFileDialog(nullptr);
    _dlg->setFileMode(QFileDialog::Directory);
    _dlg->setFilter(QDir::Dirs | QDir::Drives | QDir::Hidden | QDir::System);
    connect(_dlg, &QFileDialog::fileSelected, this,
            &DirectoryPicker::dlg_fileSelected);

    connect(_btn, &QPushButton::clicked, this, &DirectoryPicker::btn_clicked);
}
DirectoryPicker::~DirectoryPicker() { delete _dlg; }

void DirectoryPicker::dlg_fileSelected(const QString &file) {
    if (_onPick.isCallable()) {
        QJSValueList args;
        args << file;
        reportIfScriptError(_onPick.call(args));
    } else {
        _edit->setText(file);
    }
}

void DirectoryPicker::btn_clicked() {
    if (_adjustDirectory.isCallable()) {
        QJSValueList args;
        args << value();
        auto ret = _adjustDirectory.call(args);
        if (!reportIfScriptError(ret) && ret.isString()) {
            _dlg->setDirectory(ret.toString());
        }
    } else {
        _dlg->setDirectory(_edit->text());
    }
    _dlg->exec();
}

}  // namespace view
}  // namespace api
