#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QTableWidget>
#include <QFileInfo>
#include <QGraphicsScene>
#include <QThread>
#include <QObject>

class LogoAnimation;
class AboutDialog;
class Thread;
class Gear;
class StatusOne;
class OptionsDialog;
class WarningDialog;
class AbortWarningDialog;

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
    void on_pushButton_2_clicked();
    void on_actionOptions_triggered();
    void on_actionAbout_triggered();
    void on_pushButton_clicked();
    void on_actionMinimize_triggered();
    void on_smartScanButton_clicked();

    void on_actionClose_triggered();

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

};

#endif // MAINWINDOW_H
