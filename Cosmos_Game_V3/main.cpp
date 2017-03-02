/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QMediaPlayer>
#include <QTimer>
int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    //Add Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":images/splash2.png"));
    splash->show();
    Qt::Alignment bottomRight = Qt::AlignRight | Qt::AlignBottom;
    splash->showMessage(QObject::tr("Setting up the main window..."), bottomRight, Qt::white);

    MainWindow w;

    //w.setWindowFlags(Qt::FramelessWindowHint);
    w.setFixedSize(1310,780);

    QTimer::singleShot(2000,splash,SLOT(close()));
    QTimer::singleShot(2000,&w,SLOT(show()));

    return a.exec();
}
