#pragma once

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>

namespace Ui {
class InstallerWindow;
}

class InstallerWindow : public QMainWindow {
    Q_OBJECT
   public:
    explicit InstallerWindow(QWidget *parent = nullptr);
    ~InstallerWindow();

   protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

   signals:

   public slots:

   private slots:
    void bgm_stateChanged(QMediaPlayer::State state);

    void on_cancelButton_clicked();

    void on_muteButton_clicked();

   private:
    Ui::InstallerWindow *ui;
    QMediaPlayer bgm;
};
