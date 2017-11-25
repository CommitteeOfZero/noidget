#ifndef INSTALLERWINDOW_H
#define INSTALLERWINDOW_H

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
    void on_bgm_stateChanged(QMediaPlayer::State state);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

   private:
    Ui::InstallerWindow *ui;
    QMediaPlayer bgm;
};

#endif  // INSTALLERWINDOW_H
