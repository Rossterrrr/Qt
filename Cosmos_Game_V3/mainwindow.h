/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QScrollBar>
#include <QMediaPlayer>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>

class Logo;
class LevelOne;
class LevelTwo;
class LevelThree;
class LevelFour;
class LevelFive;
class OptionsWindow;
class AboutDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void timerEvent(QTimerEvent *);
    void setUp();


public slots:
    void startLevelOne();
    void endLevelOne();

    void startLevelTwo();
    void endLevelTwo();

    void startLevelThree();
    void endLevelThree();

    void startLevelFour();
    void endLevelFour();

    void startLevelFive();
    void endLevelFive();

    void startLevelSix();

    void loadFileLevelOne();
    void loadFileLevelTwo();
    void loadFileLevelThree();
    void loadFileLevelFour();
    void loadFileLevelFive();
    void loadFileLevelSix();

private slots:
    void showOptionsWindow();
    void quitGame();
   // void on_actionOptions_triggered();
    void on_actionLoad_Game_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void continueGame(int);

    void on_actionDevelopers_triggered();

protected:



private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QGraphicsView *view;

    LevelOne *levelOne;
    LevelTwo *levelTwo;
    LevelThree *levelThree;
    LevelFour *levelFour;
    LevelFive *levelFive;

    QLabel *endLevelOneScreen;
    QLabel *endLevelTwoScreen;
    QLabel *endLevelThreeScreen;
    QLabel *endLevelFourScreen;
    QLabel *endLevelFiveScreen;

    QPushButton *continueButtonL1;
    QPushButton *continueButtonL2;
    QPushButton *continueButtonL3;
    QPushButton *continueButtonL4;
    QPushButton *continueButtonL5;

    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *loadFileButton;

    Logo *logo;
    QScrollBar *scrollx;
    QScrollBar *scrolly;
    QMediaPlayer *intro;
    QMediaPlayer *music;
    OptionsWindow *optionsWindow;
    QString mFilename;

    AboutDialog *aboutDialog;

};

#endif // MAINWINDOW_H
