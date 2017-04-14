#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TransferWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_transferButton_clicked();
    void getCheckingUpdateFromTransferWindow(QString);
    void getSavingsUpdateFromTransferWindow(QString);

signals:
    void shareCheckingData(QString);
    void shareSavingsData(QString);


private:
    Ui::MainWindow *ui;
    TransferWindow *transferWindow;
};

#endif // MAINWINDOW_H
