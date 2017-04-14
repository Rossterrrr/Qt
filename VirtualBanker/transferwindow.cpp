#include "transferwindow.h"
#include "ui_transferwindow.h"
#include <QMessageBox>

TransferWindow::TransferWindow(QWidget *parent) : QDialog(parent),ui(new Ui::TransferWindow) {

    ui->setupUi(this); 

    //set fixed window size
    setFixedSize(540,100);

    //The 'f' is for float and 2 means two decimal places
    ui->AmountToTransfer->setText(QString::number(0.00,'f',2));
}

TransferWindow::~TransferWindow() {

    delete ui;
}

//A signal in MainWindow sends the current checking account info here to this slot
void TransferWindow::getCheckingAmountFromMainWin(QString n) {

    float checkingTotal = n.toFloat();
    ui->checkingAmount->setReadOnly(true);
    ui->checkingAmount->setText(QString::number(checkingTotal,'f',2));
    qDebug()<<"setting checking amount";
}

//A signal in MainWindow sends the savings checking account info here to this slot
void TransferWindow::getSavingsAmountFromMainWin(QString n) {

    float savingTotal = n.toFloat();
    ui->savingAmount->setReadOnly(true);
    ui->savingAmount->setText(QString::number(savingTotal,'f',2));
    qDebug()<<"setting saving amount";
}

//Do calculations when checking to saving button is clicked plus some error checking
void TransferWindow::on_checkingToSavings_clicked() {

    float a = ui->checkingAmount->text().toFloat();
    float b = ui->AmountToTransfer->text().toFloat();
    float c = ui->savingAmount->text().toFloat();

    if(ui->AmountToTransfer->text().isEmpty()){
        QMessageBox::warning(this, "Warning","Enter an amount to transfer");
        return;
    }
    else if(b == 0.00){
        QMessageBox::warning(this, "Warning","Transfer amount cannot be zero");
        return;
    }
    else if(b > a){
        QMessageBox::warning(this, "Warning","Transfer amount cannot be greater than available balance");
        return;
    }
    else{

    //Subtract the amount to transfer from checking amount and  update the mainwindow to reflect this change
    QString checkingCalculation = QString::number(a - b,'f',2);
    ui->checkingAmount->setText(checkingCalculation);
    emit updateCheckingBalanceInMainWin(checkingCalculation);

    //Add the amount to transfer to savings amount and also update the mainwindow to reflect this change
    QString savingsCalculation = QString::number(c + b,'f',2);
    ui->savingAmount->setText(savingsCalculation);
    emit updateSavingsBalanceInMainWin(savingsCalculation);
    QMessageBox::information(this, "Success","Transfer was completed successfully");
    ui->AmountToTransfer->setText(QString::number(0.00,'f',2));

    }
}

//Do calculations when savings to checking button is clicked plus some error checking
void TransferWindow::on_savingsToChecking_clicked() {

    float a = ui->checkingAmount->text().toFloat();
    float b = ui->AmountToTransfer->text().toFloat();
    float c = ui->savingAmount->text().toFloat();

    if(ui->AmountToTransfer->text().isEmpty()){
        QMessageBox::warning(this, "Warning","Enter an amount to transfer");
        return;
    }
    else if(b == 0.00){
        QMessageBox::warning(this, "Warning","Transfer amount cannot be zero");
        return;
    }
    else if(b > c){
        QMessageBox::warning(this, "Warning","Transfer amount cannot be greater than available balance");
        return;
    }
    else{

        //Add the amount to transfer from savings to checking  and update the MainWindow to reflect this change
        QString checkingCalculation = QString::number(a + b,'f',2);
        ui->checkingAmount->setText(checkingCalculation);
        emit updateCheckingBalanceInMainWin(checkingCalculation);

        //Subtract the amount to transfer from savings current total and update the MainWindow to reflect this change
        QString savingsCalculation = QString::number(c - b,'f',2);
        ui->savingAmount->setText(savingsCalculation);
        emit updateSavingsBalanceInMainWin(savingsCalculation);
        QMessageBox::information(this, "Success","Transfer was completed successfully");
        ui->AmountToTransfer->setText(QString::number(0.00,'f',2));
    }
}
