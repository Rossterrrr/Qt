#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QDir>
#include <QTableWidget>
#include <QFileInfo>
#include <QGraphicsScene>
#include <QThread>
#include <QTimerEvent>
#include <QDateTime>

class LogoAnimation;
class AboutDialog;
class Thread;
class ThreadTwo;
//class StopWatch;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void comboBox();
    void startAnimation();

public slots:

     void handleResult(QString data);
     void handleResultTwo(QString dataTwo);

private slots:
    void on_pushButton_2_clicked();

    void on_actionOptions_triggered();

    void on_actionAbout_triggered();

    void on_pushButton_clicked();

    void showTime();

    void on_pushButton_6_clicked();

protected:

signals:
    void finished();

private:
    Ui::MainWindow *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    QGraphicsScene *scene;
    LogoAnimation *logo;
    AboutDialog *aboutDialog;
    Thread *thread;
    ThreadTwo *threadTwo;
};

#endif // MAINWINDOW_H
