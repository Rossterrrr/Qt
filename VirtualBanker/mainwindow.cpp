#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transferwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    //Make window a fixed size
    setFixedSize(540,100);

    //Set the initial checking amount
    ui->checkingAmount->setText(QString::number(1000.00, 'f', 2));
    ui->checkingAmount->setReadOnly(true);

    //Set the initial savings amount
    ui->savingAmount->setText(QString::number(500.00,'f', 2));
    ui->savingAmount->setReadOnly(true);

    //Create the transfer window, but don't show it yet.
    transferWindow = new TransferWindow(this);

    //Setup connections between Mainwindow Signals And TransferWindow slots (Send info to TransferWindow)
    connect(this, &MainWindow::shareCheckingData, transferWindow, &TransferWindow::getCheckingAmountFromMainWin);
    connect(this, &MainWindow::shareSavingsData, transferWindow, &TransferWindow::getSavingsAmountFromMainWin);

    //Make connections for TransferWindow signals and MainWindow slots (Receive info from TransferWindow)
    connect(this->transferWindow, SIGNAL(updateCheckingBalanceInMainWin(QString)),this, SLOT(getCheckingUpdateFromTransferWindow(QString)));
    connect(this->transferWindow, SIGNAL(updateSavingsBalanceInMainWin(QString)),this, SLOT(getSavingsUpdateFromTransferWindow(QString)));
}

MainWindow::~MainWindow() {

    delete ui;
}

//Slot for the push button
void MainWindow::on_transferButton_clicked() {

    //Show the TransferWindow
    transferWindow->show();

    //Get the checking and saving amounts. Save them in a QString
    QString checkingData =ui->checkingAmount->text();
    QString savingsData = ui->savingAmount->text();

    //Emit the data so TransferWindow Can receive it
    emit shareCheckingData(checkingData);
    emit shareSavingsData(savingsData );

}

//Slot for receiving updated checking info from TransferWindow
void MainWindow::getCheckingUpdateFromTransferWindow(QString n) {

    float newCheckTotal = n.toFloat();
    ui->checkingAmount->setText(QString::number(newCheckTotal,'f',2));
    qDebug()<<" updating checking total in mainwin";
}

//Slot for receiving updated savings info from TransferWindow
void MainWindow::getSavingsUpdateFromTransferWindow(QString n) {

    float newSavingsTotal = n.toFloat();
    ui->savingAmount->setText(QString::number(newSavingsTotal,'f',2));
    qDebug()<<" updating  savings total in mainwin";
}


