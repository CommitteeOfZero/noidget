#include "installerwindow.h"
#include "ui_installerwindow.h"
#include <view/page.h>

#include <QMouseEvent>

InstallerWindow::InstallerWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::InstallerWindow) {
    setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);

    ui->headerImage->setStyleSheet(
        "background-color: #000");  // TODO parameterize

    // TODO upper right corner close/mute and reenable this
    // TODO parameterize whole window layout
    ui->muteButton->setVisible(false);

    ui->headerImage->installEventFilter(this);

    connect(&bgm, &QMediaPlayer::stateChanged, this,
            &InstallerWindow::bgm_stateChanged);
}

InstallerWindow::~InstallerWindow() { delete ui; }

bool InstallerWindow::eventFilter(QObject *watched, QEvent *event) {
    static QPoint lastPos;
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        lastPos = mouseEvent->globalPos();
        event->accept();
        return true;
    }
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        move(pos() + (mouseEvent->globalPos() - lastPos));
        lastPos = mouseEvent->globalPos();
        event->accept();
        return true;
    }

    return false;
}

void InstallerWindow::bgm_stateChanged(QMediaPlayer::State state) {
    if (state == QMediaPlayer::StoppedState) {
        bgm.play();
    }
}

void InstallerWindow::on_cancelButton_clicked() { close(); }

void InstallerWindow::on_muteButton_clicked() {
    bgm.state() == QMediaPlayer::PlayingState ? bgm.pause() : bgm.play();
}

void InstallerWindow::push(view::Page *page) {
    connect(page, &view::Page::popRequested, this,
            &InstallerWindow::page_popRequested);
    const int i = ui->stackedWidget->addWidget(page);
    ui->stackedWidget->setCurrentIndex(i);  // TODO necessary?
}

void InstallerWindow::pop() {
    view::Page *top = currentPage();
    removePage(top);
}

view::Page *InstallerWindow::currentPage() {
    return qobject_cast<view::Page *>(ui->stackedWidget->currentWidget());
}

void InstallerWindow::setBgm(const QUrl &url) {
    bgm.setMedia(url);
    bgm.setVolume(50);
    bgm.play();
}

void InstallerWindow::on_nextButton_clicked() {
    view::Page *top = currentPage();
    if (top != nullptr) {
        top->next();
    }
}

void InstallerWindow::on_backButton_clicked() {
    view::Page *top = currentPage();
    if (top != nullptr) {
        top->back();
    }
}

void InstallerWindow::on_stackedWidget_currentChanged(int i) {
    ui->backButton->setEnabled(ui->stackedWidget->count() > 1);
}

void InstallerWindow::page_popRequested() {
    view::Page *page = qobject_cast<view::Page *>(sender());
    removePage(page);
}

void InstallerWindow::removePage(view::Page *page) {
    if (page != nullptr) {
        disconnect(page, 0, this, 0);
        disconnect(this, 0, page, 0);

        ui->stackedWidget->removeWidget(page);
        delete page;
    }
}