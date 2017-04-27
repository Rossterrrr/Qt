#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QTableWidget>
#include <QFileInfo>
#include <QGraphicsScene>
#include <QThread>
#include <QObject>
#include <QFileDialog>
#include <QStringList>
#include <QFileInfo>

class LogoAnimation;
class AboutDialog;
class Thread;
class Gear;
class StatusOne;
class OptionsDialog;
class WarningDialog;
class AbortWarningDialog;
class SingleScanThread;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startAnimation();
    void startGearAnimation();

public slots:
     void handleScanStart();
     void handleScanComplete();
     void displayInfectedFiles(QString);
     void stopThread();

private slots:
    void on_abort_clicked();
    void on_actionOptions_triggered();
    void on_actionAbout_triggered();
    void on_scanDirectory_clicked();
    void on_actionMinimize_triggered();
    void on_smartScanButton_clicked();

    void on_actionClose_triggered();

    void on_scanSingleFile_clicked();

    void on_removeSelectedFile_clicked();

    void on_removeAllFiles_clicked();



    void on_removeSelectedFile_released();

    void on_removeAllFiles_released();

    void on_abort_released();

    void on_smartScanButton_released();

    void on_scanSingleFile_released();

    void on_scanDirectory_released();

    void on_actionOptions_hovered();

    void on_actionAbout_hovered();

    void on_actionMinimize_hovered();

    void on_actionClose_hovered();

signals:
    void finished();
    void scanType(QString);
    void stopTheTimer();

private:
    Ui::MainWindow *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    QGraphicsScene *scene;
    QGraphicsScene *sceneTwo;
    LogoAnimation *logo;
    AboutDialog *aboutDialog;
    Thread *thread;
    Gear *gear;
    StatusOne *textOne;
    StatusOne *textTwo;
    StatusOne *threatText;
    StatusOne *mainLogo;
    bool checkTextOne;
    bool checkTextTwo;
    OptionsDialog *optionsDialog;
    WarningDialog *warningDialog;
    AbortWarningDialog *abortWarningDialog;
    QString *fileName;
    SingleScanThread *singleScanThread;
    bool stopMouseMovement;

};

#endif // MAINWINDOW_H
