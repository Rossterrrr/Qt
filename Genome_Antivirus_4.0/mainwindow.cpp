#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logoanimation.h"
#include <QPainter>
#include "logoanimation.h"
#include "aboutdialog.h"
#include "thread.h"
#include<QDebug>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);  
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,121,81);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    comboBox();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::comboBox() {

    ui->comboBox->addItem(" Select Scan Type");
    ui->comboBox->addItem(" Quick Scan");
    ui->comboBox->addItem(" Full System Scan");
    ui->comboBox->addItem(" Boot Time Scan");
}

void MainWindow::startAnimation() {

    ui->label_2->close();
    logo = new LogoAnimation();
    logo->setPos(5, 18);
    scene->addItem(logo);
}

void MainWindow::on_pushButton_clicked() {

    if(ui->comboBox->currentText()== " Quick Scan") {

        QStringList list;
        list<< "G:/" << "J:/";
        thread = new Thread(list);
    }
    else if(ui->comboBox->currentText()== " Full System Scan") {

        QStringList list;
        list<< "C:/" << "D:/";
        thread = new Thread(list);
    }
    else if(ui->comboBox->currentText()== " Select Scan Type") {

        return;
    }
    else if(ui->comboBox->currentText()== " Boot Time Scan") {

        return;
    }
    else{

        return;
    }

    connect(thread, &Thread::scanStart, this, &MainWindow::handleScanStart);
    connect(thread, &Thread::scanComplete, this, &MainWindow::handleScanComplete);
    connect(thread, &Thread::infectedFiles, this, &MainWindow::displayInfectedFiles);
    connect(thread, &Thread::finished, thread, &QObject::deleteLater);
    thread->start();
    startAnimation();
}

void MainWindow::handleScanStart(int n) {

    int number = n;

    if(number == 1){
        ui->label_5->setText("Processing");
    }else{
        return;
    }
}

void MainWindow::handleScanComplete(int n) {

    int number = n;

    if(number == 3){
        delete logo;
        ui->label_2->show();
        ui->label_5->setText("Complete");
    }else{
        return;
    }

}

void MainWindow::displayInfectedFiles(QString files) {

    QString infectedFiles = files;
    ui->listWidget->addItem(infectedFiles);
}

void MainWindow::on_actionMinimize_triggered() {

   MainWindow::showMinimized();
}

void MainWindow::on_actionOptions_triggered() {

}

void MainWindow::on_pushButton_2_clicked() {

    qApp->quit();
}

void MainWindow::on_actionAbout_triggered() {

    aboutDialog = new AboutDialog();
    aboutDialog->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|
                                Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
    aboutDialog->exec();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {

    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}
