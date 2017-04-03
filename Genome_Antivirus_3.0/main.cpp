#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.setFixedSize(650,416);
    w.show();

    return a.exec();
}
