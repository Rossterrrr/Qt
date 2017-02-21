/*
 * Author: Jonathan Baird
 * Date: 1/29/2017
 * Purpose: MVC SEC Video Game Punk Rift
*/


#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/audio/intro.mp3"));
    //music->play();

    //Add Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":images/splash2.png"));
    splash->show();

    MainWindow w;

    //w.setWindowFlags(Qt::FramelessWindowHint);
    w.setFixedSize(1310,780);

    QTimer::singleShot(30,splash,SLOT(close()));
    QTimer::singleShot(30,&w,SLOT(show()));



    return a.exec();
}
