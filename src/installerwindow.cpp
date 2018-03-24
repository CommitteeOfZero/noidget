#include "installerwindow.h"
#include "ui_installerwindow.h"
#include <view/page.h>

#include <QMouseEvent>
#include <QToolButton>

InstallerWindow::InstallerWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::InstallerWindow) {
    setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);

    ui->headerImage->setStyleSheet(
        "background-color: #000");  // TODO parameterize

    // TODO parameterize whole window layout

    ui->headerImage->installEventFilter(this);

    connect(&bgm, &QMediaPlayer::stateChanged, this,
            &InstallerWindow::bgm_stateChanged);

    // gross but I haven't found any way to overlay a container over other
    // widgets while passing through input events that don't hit any of its
    // child widgets
    QToolButton *crossButton = new QToolButton(this);
    crossButton->setStyleSheet(
        "QToolButton { image: url(':/cross.png'); }"
        "QToolButton:hover { image: url(':/cross_hover.png'); }");
    crossButton->setCursor(QCursor(Qt::PointingHandCursor));
    crossButton->resize(18, 18);
    crossButton->move(width() - (crossButton->width() + 12), 12);
    connect(crossButton, &QAbstractButton::clicked, this,
            &InstallerWindow::on_cancelButton_clicked);
    QToolButton *muteButton = new QToolButton(this);
    muteButton->setStyleSheet(
        "QToolButton { image: url(':/mute.png'); }"
        "QToolButton:hover { image: url(':/mute_hover.png'); }");
    muteButton->setCursor(QCursor(Qt::PointingHandCursor));
    muteButton->resize(18, 18);
    muteButton->move(crossButton->x() - (muteButton->width() + 8), 12);
    connect(muteButton, &QAbstractButton::clicked, this,
            &InstallerWindow::on_muteButton_clicked);
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
    ui->backButton->setEnabled(true);
    ui->nextButton->setEnabled(true);
    connect(page, &view::Page::nextEnabled, this,
            &InstallerWindow::page_nextEnabled);
    connect(page, &view::Page::backEnabled, this,
            &InstallerWindow::page_backEnabled);
    connect(page, &view::Page::popRequested, this,
            &InstallerWindow::page_popRequested);
    const int i = ui->stackedWidget->addWidget(page);
    ui->stackedWidget->setCurrentIndex(i);  // TODO necessary?
    page->attached();
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

void InstallerWindow::page_nextEnabled(bool enabled) {
    ui->nextButton->setEnabled(enabled);
}

void InstallerWindow::page_backEnabled(bool enabled) {
    ui->backButton->setEnabled(enabled);
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