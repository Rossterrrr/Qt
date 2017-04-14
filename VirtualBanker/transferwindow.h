#ifndef TRANSFERWINDOW_H
#define TRANSFERWINDOW_H

#include <QDialog>
#include "QDebug"

namespace Ui {
class TransferWindow;
}

class TransferWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TransferWindow(QWidget *parent = 0);
    ~TransferWindow();


public slots:
    void getCheckingAmountFromMainWin(QString);
    void getSavingsAmountFromMainWin(QString);


signals:
    void updateCheckingBalanceInMainWin(QString);
    void updateSavingsBalanceInMainWin(QString);

private slots:


    void on_checkingToSavings_clicked();

    void on_savingsToChecking_clicked();

private:
    Ui::TransferWindow *ui;


};

#endif // TRANSFERWINDOW_H
