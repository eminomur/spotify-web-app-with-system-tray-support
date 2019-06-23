#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Following line of code makes windows neither maximize nor minimize
    // I needed this because web page is also set to 720x1280 resolution
    w.setFixedSize(1280, 720);

    w.show();

    return a.exec();
}
