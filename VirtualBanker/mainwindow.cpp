#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transferwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setFixedSize(540,100);
    ui->checkingAmount->setText(QString::number(1000.00, 'f', 2));
    ui->checkingAmount->setReadOnly(true);

    ui->savingAmount->setText(QString::number(500.00,'f', 2));
    ui->savingAmount->setReadOnly(true);

    transferWindow = new TransferWindow(this);
    connect(this, &MainWindow::shareCheckingData, transferWindow, &TransferWindow::getCheckingAmountFromMainWin);
    connect(this, &MainWindow::shareSavingsData, transferWindow, &TransferWindow::getSavingsAmountFromMainWin);

}

MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::on_transferButton_clicked() {

 transferWindow->show();
 QString checkingData =ui->checkingAmount->text();
 QString savingsData = ui->savingAmount->text();
 emit shareCheckingData(checkingData);
 emit shareSavingsData(savingsData );
 connect(this->transferWindow, SIGNAL(updateCheckingBalanceInMainWin(QString)),this, SLOT(getCheckingUpdateFromTransferWindow(QString)));
 connect(this->transferWindow, SIGNAL(updateSavingsBalanceInMainWin(QString)),this, SLOT(getSavingsUpdateFromTransferWindow(QString)));
}

void MainWindow::getCheckingUpdateFromTransferWindow(QString n) {

    float newCheckTotal = n.toFloat();
    ui->checkingAmount->setText(QString::number(newCheckTotal,'f',2));
    qDebug()<<" updating checking total in mainwin";

}

void MainWindow::getSavingsUpdateFromTransferWindow(QString n) {

    float newSavingsTotal = n.toFloat();
    ui->savingAmount->setText(QString::number(newSavingsTotal,'f',2));
    qDebug()<<" updating  savings total in mainwin";
}


