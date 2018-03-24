#pragma once

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <QEvent>
#include <QCloseEvent>
#include <view/ipagestack.h>
#include "installerapplication.h"

namespace Ui {
class InstallerWindow;
}

namespace view {
class Page;
}

class InstallerWindow : public QMainWindow, public view::IPageStack {
    Q_OBJECT
   public:
    explicit InstallerWindow(QWidget *parent = nullptr);
    ~InstallerWindow();

    void push(view::Page *page) override;
    void pop() override;
    view::Page *currentPage() override;

    void setBgm(const QUrl &url);

   protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

   signals:

   public slots:

   private slots:
    void handleAppStateChange(InstallerApplication::State newState);

    void bgm_stateChanged(QMediaPlayer::State state);
    void cancelRequested();
    void on_muteButton_clicked();

    void on_nextButton_clicked();
    void on_backButton_clicked();
    void on_stackedWidget_currentChanged(int i);

    void page_popRequested();
    void page_nextEnabled(bool enabled);
    void page_backEnabled(bool enabled);

   private:
    Ui::InstallerWindow *ui;
    QMediaPlayer bgm;

    void removePage(view::Page *page);
};
