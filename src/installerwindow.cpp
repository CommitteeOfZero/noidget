#include "installerwindow.h"
#include "ui_installerwindow.h"
#include <view/page.h>
#include "installerapplication.h"
#include <tx/transaction.h>

#include <QMouseEvent>
#include <QToolButton>
#include <QMessageBox>

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
            &InstallerWindow::cancelRequested);
    QToolButton *muteButton = new QToolButton(this);
    muteButton->setStyleSheet(
        "QToolButton { image: url(':/mute.png'); }"
        "QToolButton:hover { image: url(':/mute_hover.png'); }");
    muteButton->setCursor(QCursor(Qt::PointingHandCursor));
    muteButton->resize(18, 18);
    muteButton->move(crossButton->x() - (muteButton->width() + 8), 12);
    connect(muteButton, &QAbstractButton::clicked, this,
            &InstallerWindow::on_muteButton_clicked);

    connect(ngApp, &InstallerApplication::currentStateChanged, this,
            &InstallerWindow::handleAppStateChange);
    connect(ui->cancelButton, &QAbstractButton::clicked, this,
            &InstallerWindow::cancelRequested);
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

void InstallerWindow::handleAppStateChange(
    InstallerApplication::State newState) {
    switch (newState) {
        case InstallerApplication::State::Installing:
            ui->nextButton->setEnabled(false);
            ui->backButton->setEnabled(false);
            break;
        case InstallerApplication::State::Finished:
            ui->nextButton->setText("Finish");
            ui->nextButton->setEnabled(true);
            ui->backButton->setEnabled(false);
            ui->cancelButton->setEnabled(false);
            break;
        case InstallerApplication::State::Cancelled:
            ui->nextButton->setText("Quit");
            ui->nextButton->setEnabled(true);
            ui->backButton->setEnabled(false);
            ui->cancelButton->setEnabled(false);
            break;
    }
}

void InstallerWindow::bgm_stateChanged(QMediaPlayer::State state) {
    if (state == QMediaPlayer::StoppedState) {
        bgm.play();
    }
}

void InstallerWindow::closeEvent(QCloseEvent *event) {
    event->ignore();
    cancelRequested();
}

void InstallerWindow::cancelRequested() {
    if (ngApp->currentState() == InstallerApplication::State::Cancelled ||
        ngApp->currentState() == InstallerApplication::State::Finished) {
        // X button, alt+f4
        QApplication::quit();
        return;
    }

    QString question = "Really abort the installation?";
    if (ngApp->currentState() == InstallerApplication::State::Installing) {
        question +=
            "\n\nChanges already made by the installer will not be undone!";
    }
    QMessageBox mb(this);
    mb.setText(question);
    mb.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (mb.exec() != QMessageBox::Yes) return;

    // This is kinda racey...
    if (ngApp->currentState() == InstallerApplication::State::Installing) {
        ngApp->setCurrentState(InstallerApplication::State::Cancelled);
    } else {
        QApplication::quit();
    }
}

void InstallerWindow::on_muteButton_clicked() {
    bgm.state() == QMediaPlayer::PlayingState ? bgm.pause() : bgm.play();
}

void InstallerWindow::push(view::Page *page) {
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
    if (ui->stackedWidget->count() <= 1) {
        ui->backButton->setEnabled(false);
    }
}

void InstallerWindow::page_nextEnabled(bool enabled) {
    ui->nextButton->setEnabled(enabled);
}

void InstallerWindow::page_backEnabled(bool enabled) {
    ui->backButton->setEnabled(ui->stackedWidget->count() > 1 && enabled);
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