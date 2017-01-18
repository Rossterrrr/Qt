#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    //w.setStyleSheet("background:transparent");
   // w.setAttribute(Qt::WA_TranslucentBackground);
    //w.setProperty("windowOpacity", 0.5);
    w.show();

    return a.exec();
}
