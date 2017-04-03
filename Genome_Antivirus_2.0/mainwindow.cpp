#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logoanimation.h"
#include <QPainter>
#include <QDebug>
#include "logoanimation.h"
#include <QDirIterator>
#include <QDir>
#include "aboutdialog.h"
#include <QTimer>
#include <QDateTime>
#include "thread.h"
#include "threadtwo.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    comboBox();

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,121,81);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->progressBar->setValue(0);
    //ui->lineEdit->setStyleSheet("color: #FFFFFF");

    QTimer *timer = new QTimer(this);
    connect(timer ,SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(100);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::comboBox() {

    ui->comboBox->addItem(" Quick scan");
    ui->comboBox->addItem(" Full system scan");
    ui->comboBox->addItem(" Boot time scan");
}

void MainWindow::startAnimation() {

    ui->label_2->close();
    logo = new LogoAnimation();
    logo->setPos(15, 17);
    scene->addItem(logo);

}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {

    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}


void MainWindow::on_pushButton_2_clicked() {

    qApp->quit();
}

void MainWindow::on_actionOptions_triggered() {

}

void MainWindow::on_actionAbout_triggered() {

     aboutDialog = new AboutDialog();
     aboutDialog->setWindowFlags(Qt::FramelessWindowHint);
     aboutDialog->exec();
}

void MainWindow::on_pushButton_clicked() {

    thread = new Thread();
    connect(thread, &Thread::result, this, &MainWindow::handleResult);
    connect(thread, &Thread::resultTwo, this, &MainWindow::handleResultTwo);
    connect(thread, &Thread::finished, thread, &QObject::deleteLater);
    thread->start();

    //threadTwo = new ThreadTwo();
    //connect(threadTwo, &ThreadTwo::resultTwo, this, &MainWindow::handleResultTwo);
    //connect(threadTwo, &ThreadTwo::finished, threadTwo, &QObject::deleteLater);
    //threadTwo->start();

    startAnimation();
    showTime();
}

void MainWindow::showTime() {

    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->lineEdit_2->setText(time_text);

}

void MainWindow::on_pushButton_6_clicked() {

}

void MainWindow::handleResult(QString data) {

    QString numberOfFiles = data;
    ui->lineEdit_3->setText(numberOfFiles);
}

void MainWindow::handleResultTwo(QString dataTwo) {

    QString infectedFiles = dataTwo;
    ui->listWidget->addItem(infectedFiles);
}




