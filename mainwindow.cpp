#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWebEngineView>
#include <QUrl>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QSystemTrayIcon>
#include <QCoreApplication>
#include <QMenu>
#include <QIcon>
#include <QAction>
#include <QWidget>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // This fixed size seems to okay with my screen resolution
    // You are free to change these values
    this->resize(1280, 720);

    create_actions();
    create_tray_icon();

    // Following line of code makes possible making window visible, insivisible with a click
    // on system tray icon
    connect(app_tray_icon, &QSystemTrayIcon::activated, this, &MainWindow::icon_activated);

    view = new QWebEngineView(this);
    view->load(QUrl("https://open.spotify.com/browse/featured"));
    view->setGeometry(0, 0, this->width(), this->height());
    view->show();

    app_tray_icon->show();
}

void MainWindow::create_tray_icon()
{
    app_tray_icon_menu = new QMenu(this);
    app_tray_icon_menu->addAction(change_window_status_action);
    app_tray_icon_menu->addSeparator();
    app_tray_icon_menu->addAction(about_me_action);
    app_tray_icon_menu->addAction(about_software_action);
    app_tray_icon_menu->addSeparator();
    app_tray_icon_menu->addAction(quit_action);

    app_tray_icon = new QSystemTrayIcon(this);
    app_tray_icon->setIcon(QIcon(":/rsc/Resource/spotify.png"));
    app_tray_icon->setContextMenu(app_tray_icon_menu);
}

void MainWindow::create_actions()
{
    change_window_status_action = new QAction(QIcon(":/rsc/Resource/spotify.png"), "Spoti-Tray", this);
    connect(change_window_status_action, &QAction::triggered, this, &MainWindow::change_window_status);

    hide_action = new QAction("Hide", this);
    connect(hide_action, &QAction::triggered, this, &QWidget::hide);
    hide_action->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_W));

    quit_action = new QAction("Quit", this);
    connect(quit_action, &QAction::triggered, this, &QCoreApplication::quit);
    quit_action->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));

    about_me_action = new QAction("About Me", this);
    connect(about_me_action, &QAction::triggered, this, &MainWindow::about_me);

    about_software_action = new QAction("About Software", this);
    connect(about_software_action, &QAction::triggered, this, &MainWindow::about_software);
    about_software_action->setShortcut(QKeySequence(Qt::Key_F1));

    addActions({hide_action, quit_action, about_software_action});
}

void MainWindow::delete_actions()
{
    delete hide_action;
    delete quit_action;
    delete about_me_action;
    delete about_software_action;
}

void MainWindow::about_me() const
{
    QMessageBox::about(nullptr, "About Me", "Muhammed Emin ÖMÜR\nSoftware Engineering Student");
}

void MainWindow::about_software() const
{
    QMessageBox::about(nullptr, "About", "1) I developed this because Spotify in Linux lacks some important features which are available in Windows or (not sure) MacOS.\n"
                                         "2) You are free to use.\n"
                                         "3) I hope this program will be helpful to Linux users.\n");
}

void MainWindow::change_window_status()
{
    if (this->isVisible()) {
        this->hide();
    } else {
        this->show();
    }
}

void MainWindow::icon_activated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        change_window_status();
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete_actions();

    delete app_tray_icon_menu;
    delete app_tray_icon;

    delete view;

    delete ui;
}
