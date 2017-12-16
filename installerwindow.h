#pragma once

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <QEvent>
#include "view/ipagestack.h"
#include "view/page.h"

namespace Ui {
class InstallerWindow;
}

class InstallerWindow : public QMainWindow, public view::IPageStack {
    Q_OBJECT
   public:
    explicit InstallerWindow(QWidget *parent = nullptr);
    ~InstallerWindow();

    void push(view::Page *page) override;
    void pop() override;
    view::Page *currentPage() override;

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
