#include "installerwindow.h"
#include "ui_installerwindow.h"

InstallerWindow::InstallerWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::InstallerWindow) {
    setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);

    ui->headerImage->installEventFilter(this);

    connect(&bgm, &QMediaPlayer::stateChanged, this,
            &InstallerWindow::on_bgm_stateChanged);
    bgm.setMedia(QUrl("qrc:/bgm.mp3"));
    bgm.setVolume(50);
    bgm.play();
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

void InstallerWindow::on_bgm_stateChanged(QMediaPlayer::State state) {
    if (state == QMediaPlayer::StoppedState) {
        bgm.play();
    }
}

void InstallerWindow::on_pushButton_3_clicked() { close(); }

void InstallerWindow::on_pushButton_4_clicked() {
    bgm.state() == QMediaPlayer::PlayingState ? bgm.pause() : bgm.play();
}
