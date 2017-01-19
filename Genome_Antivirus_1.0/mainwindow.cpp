#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
   // Qt::FramelessWindowHint;
    comboBox();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::comboBox() {

    ui->comboBox->addItem(" Quick scan");
    ui->comboBox->addItem(" Full system scan");
    ui->comboBox->addItem(" Boot time scan");
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

}

void MainWindow::on_pushButton_clicked() {

    QDir dir("C:/");

    foreach(QFileInfo mItm, dir.entryInfoList()){

        qDebug() << mItm.absoluteFilePath();
        ui->listWidget->addItem(mItm.absoluteFilePath());

    }

}
