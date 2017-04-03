#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QTableWidget>
#include <QFileInfo>
#include <QGraphicsScene>

class LogoAnimation;
class AboutDialog;
class Thread;

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
     void handleScanStart(int);
     void handleScanComplete(int);
     void displayInfectedFiles(QString data);

private slots:
    void on_pushButton_2_clicked();
    void on_actionOptions_triggered();
    void on_actionAbout_triggered();
    void on_pushButton_clicked();
    void on_actionMinimize_triggered();

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

};

#endif // MAINWINDOW_H
