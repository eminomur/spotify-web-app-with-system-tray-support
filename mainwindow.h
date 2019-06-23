#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void icon_activated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;

    QWebEngineView *view;

    QSystemTrayIcon *app_tray_icon;
    QMenu *app_tray_icon_menu;

    QAction *change_window_status_action;
    QAction *hide_action;
    QAction *quit_action;
    QAction *about_me_action;
    QAction *about_software_action;

    void create_actions();
    void create_tray_icon();
    void delete_actions();

    void about_me() const;
    void about_software() const;

    // Making application window visible if it is invisible or vice versa
    void change_window_status();
};

#endif // MAINWINDOW_H
