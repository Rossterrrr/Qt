/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logo.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "levelfive.h"
//#include "optionswindow.h"
#include "aboutdialog.h"
#include <QPainter>
#include <QDebug>
#include <QTimerEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setUp();
}

MainWindow::~MainWindow() {
    delete ui;
}

//Timer event for logo animation
void MainWindow::timerEvent(QTimerEvent *) {

logo->nextFrame();

}

//Title screen setup
void MainWindow::setUp() {

    //Add intro music
    intro = new QMediaPlayer();
    intro->setMedia(QUrl("qrc:/audio/intro.mp3"));
    intro->play();

    //Add level one music
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/audio/levelOne.mp3"));

    //Add  scene
    scene = new QGraphicsScene();
    //scene->setSceneRect(0,0,1310,1520);

    //Add  view
    view = new QGraphicsView();
    view->setStyleSheet("background-image: url(:images/cosmoslogo.png)");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  
    view->setTransformationAnchor(QGraphicsView::NoAnchor);
    view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->setCacheMode(QGraphicsView::CacheBackground);

    //Open gl testing not working
    //view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    //view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::Rgba)));


    view->setScene(scene);
    setCentralWidget(view);

    //Add scroll
    scrollx = new QScrollBar;
    scrollx = view->horizontalScrollBar();

    scrolly = new QScrollBar;
    scrolly = view->verticalScrollBar();

    //Add logo
    logo = new Logo();
    logo->setPos(20,20);
    //scene->addItem(logo);
    startTimer( 100 );

    //Add start button
    startButton = new QPushButton(this);
    startButton->setText("Start");
    startButton->setStyleSheet("color:white;");
    startButton->setFlat(true);
    QFont font = startButton->font();
    font.setPointSize(20);
    startButton->setFont(font);
    startButton->setGeometry(QRect(533, 500, 100, 32));
    connect(startButton, SIGNAL(clicked()), this, SLOT(startLevelOne()));

    //Add Quit Button
    quitButton = new QPushButton(this);
    quitButton->setText("Quit");
    quitButton->setStyleSheet("color:white;");
    quitButton->setFlat(true);
    QFont font2 = startButton->font();
    font.setPointSize(20);
    quitButton->setFont(font2);
    quitButton->setGeometry(QRect(690, 500, 100, 32));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitGame()));

/*
    //Add Continue/loadfile Button
    loadFileButton = new QPushButton(this);
    loadFileButton->setText("Continue");
    loadFileButton->setStyleSheet("color:white;");
    loadFileButton->setFlat(true);
    QFont font3 = startButton->font();
    font.setPointSize(20);
    loadFileButton->setFont(font3);
    loadFileButton->setGeometry(QRect(690, 600, 100, 50));
    connect(loadFileButton, SIGNAL(clicked()), this, SLOT(open()));
    */
}

//---------------------------------------------------------------------------------Start a new game-------------------------------------------------------//

//Start level one
void MainWindow::startLevelOne() {

    intro->stop();
    //music->play();
    startButton->close();
    quitButton->close();
    //view->setStyleSheet("background-color: black");
    view->setStyleSheet("background-image: url(:images/levelClear.png)");
    levelOne = new LevelOne(scrollx,scrolly);
    view->setScene(levelOne);
    connect(this->levelOne, SIGNAL(endLevelOne()),this, SLOT(endLevelOne()));   \
}

//End level one
void MainWindow::endLevelOne() {

    music->stop();
    delete levelOne;

    QPixmap pic (":images/clear1.png");
    endLevelOneScreen = new QLabel(this);
    endLevelOneScreen->setGeometry(QRect(0, 22, 1310, 760));
    endLevelOneScreen->setPixmap(pic);
    endLevelOneScreen->show();
    continueButtonL1 = new QPushButton(this);
    continueButtonL1->setStyleSheet("color:white;");
    continueButtonL1->setFlat(true);
    QFont font = startButton->font();
    font.setPointSize(20);
    continueButtonL1->setFont(font);
    continueButtonL1->setGeometry(QRect(600, 500, 115, 32));
    continueButtonL1->setText("Continue");
    continueButtonL1->show();
    connect(continueButtonL1, SIGNAL(clicked()), this, SLOT(startLevelTwo()));
}

//Start level two
void MainWindow::startLevelTwo() {

    continueButtonL1->close();
    endLevelOneScreen->close();

    levelTwo = new LevelTwo(scrollx,scrolly);
    view->setStyleSheet("background-image: url(:images/levelClear2.png)");
    view->setScene(levelTwo);
    connect(this->levelTwo, SIGNAL(endLevelTwo()),this, SLOT(endLevelTwo()));
}

//End level two
void MainWindow::endLevelTwo() {

    delete levelTwo;

    QPixmap picTwo (":images/clear2.png");
    endLevelTwoScreen = new QLabel(this);
    endLevelTwoScreen->setGeometry(QRect(0, 22, 1310, 760));
    endLevelTwoScreen->setPixmap(picTwo);
    endLevelTwoScreen->show();
    continueButtonL2 = new QPushButton(this);
    continueButtonL2->setStyleSheet("color:white;");
    continueButtonL2->setFlat(true);
    QFont font = continueButtonL2->font();
    font.setPointSize(20);
    continueButtonL2->setFont(font);
    continueButtonL2->setGeometry(QRect(600, 500, 115, 32));
    continueButtonL2->setText("Continue");
    continueButtonL2->show();
    connect(continueButtonL2 , SIGNAL(clicked()), this, SLOT(startLevelThree()));

}

//Start level three
void MainWindow::startLevelThree(){

    continueButtonL2->close();
    endLevelTwoScreen->close();

    levelThree = new LevelThree(scrollx,scrolly);
    view->setScene(levelThree);
    view->setStyleSheet("background-image: url(:images/levelClear3.png)");
    connect(this->levelThree, SIGNAL(endLevelThree()),this, SLOT(endLevelThree()));
}

//End level three
void MainWindow::endLevelThree() {

    delete levelThree;

    QPixmap picTwo (":images/clear3.png");
    endLevelThreeScreen = new QLabel(this);
    endLevelThreeScreen->setGeometry(QRect(0, 22, 1310, 760));
    endLevelThreeScreen->setPixmap(picTwo);
    endLevelThreeScreen->show();
    continueButtonL3 = new QPushButton(this);
    continueButtonL3->setStyleSheet("color:white;");
    continueButtonL3->setFlat(true);
    QFont font = continueButtonL3->font();
    font.setPointSize(20);
    continueButtonL3->setFont(font);
    continueButtonL3->setGeometry(QRect(600, 500, 115, 32));
    continueButtonL3->setText("Continue");
    continueButtonL3->show();
    connect(continueButtonL3 , SIGNAL(clicked()), this, SLOT(startLevelFour()));
}

//Start level four
void MainWindow::startLevelFour(){

    continueButtonL3->close();
    endLevelThreeScreen->close();

    levelFour = new LevelFour(scrollx,scrolly);
    view->setScene(levelFour);
    view->setStyleSheet("background-image: url(:images/levelClear4.png)");
    connect(this->levelFour, SIGNAL(endLevelFour()),this, SLOT(endLevelFour()));
}

//End level four
void MainWindow::endLevelFour() {

    delete levelFour;

    QPixmap picTwo (":images/clear4.png");
    endLevelFourScreen = new QLabel(this);
    endLevelFourScreen->setGeometry(QRect(0, 22, 1310, 760));
    endLevelFourScreen->setPixmap(picTwo);
    endLevelFourScreen->show();
    continueButtonL4 = new QPushButton(this);
    continueButtonL4->setStyleSheet("color:white;");
    continueButtonL4->setFlat(true);
    QFont font = continueButtonL4->font();
    font.setPointSize(20);
    continueButtonL4->setFont(font);
    continueButtonL4->setGeometry(QRect(600, 500, 115, 32));
    continueButtonL4->setText("Continue");
    continueButtonL4->show();
    connect(continueButtonL4 , SIGNAL(clicked()), this, SLOT(startLevelFive()));
}

//Start level five
void MainWindow::startLevelFive() {

    continueButtonL4->close();
    endLevelFourScreen->close();

    levelFive = new LevelFive(scrollx,scrolly);
    view->setScene(levelFive);
    view->setStyleSheet("background-image: url(:images/levelClear5_2.png)");
    connect(this->levelFive, SIGNAL(endLevelFive()),this, SLOT(endLevelFive()));
}

//End level five
void MainWindow::endLevelFive() {

    delete levelFive;

    QPixmap picTwo (":images/clear5.png");
    endLevelFiveScreen = new QLabel(this);
    endLevelFiveScreen->setGeometry(QRect(0, 22, 1310, 760));
    endLevelFiveScreen->setPixmap(picTwo);
    endLevelFiveScreen->show();
    continueButtonL5 = new QPushButton(this);
    continueButtonL5->setStyleSheet("color:white;");
    continueButtonL5->setFlat(true);
    QFont font = continueButtonL5->font();
    font.setPointSize(20);
    continueButtonL5->setFont(font);
    continueButtonL5->setGeometry(QRect(600, 500, 115, 32));
    continueButtonL5->setText("Continue");
    continueButtonL5->show();
    connect(continueButtonL5 , SIGNAL(clicked()), this, SLOT(startLevelSix()));

}

void MainWindow::startLevelSix() {

    qApp->quit();
}

void MainWindow::showOptionsWindow() {

    //optionsWindow = new OptionsWindow();
    //optionsWindow->exec();
}

void MainWindow::quitGame() {

        qApp->quit();

}

//void MainWindow::on_actionOptions_triggered() {

   // optionsWindow = new OptionsWindow();
   // optionsWindow->exec();
//}

//---------------------------------------------------------------------------------File IO-----------------------------------------------------------------------//

//Search for the file to open
void MainWindow::on_actionLoad_Game_triggered() {

    QString file = QFileDialog::getOpenFileName(this,"Open a file");

    if(!file.isEmpty())
    {
        QFile sFile(file);
        if(sFile.open(QFile::ReadOnly | QFile::Text))
        {
            mFilename = file;
            QTextStream in(&sFile);
            QString text = in.readAll();
            sFile.close();
            continueGame(text.toInt());
        }
    }
}

//Save game progress
void MainWindow::on_actionSave_triggered() {
    //Test for filename
    QFile sFile(mFilename);
    if(sFile.open(QFile::WriteOnly |  QFile::Text))
    {
        QTextStream out(&sFile);

        // out << ui->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}

//Save game progress to a new file
void MainWindow::on_actionSave_As_triggered() {

    QString file = QFileDialog::getSaveFileName(this,"Open a file");

    if(!file.isEmpty())
    {
        mFilename = file;
        on_actionSave_triggered();
    }
}

//Receive info form the file and perform the necessary action
void MainWindow::continueGame(int n) {

    int option = n;

    if(option == 1) {

        loadFileLevelOne();
    }
    else if(option == 2)  {

        loadFileLevelTwo();
    }
    else if(option == 3) {

        loadFileLevelThree();
    }
    else if(option == 4) {

        loadFileLevelFour();
    }
    else if(option == 5) {

        loadFileLevelFive();
    }
    else if(option == 6) {

        loadFileLevelSix();
    }
    else {

        //Display an error
    }

}

//-------------------------------------------------------------------------------Start game from file---------------------------------------------------------//

void MainWindow::loadFileLevelOne() {

    intro->stop();
    music->play();
    startButton->close();
    quitButton->close();
    //view->setStyleSheet("background-color: black");
    view->setStyleSheet("background-image: url(:images/levelClear.png)");
    levelOne = new LevelOne(scrollx,scrolly);
    view->setScene(levelOne);
    connect(this->levelOne, SIGNAL(endLevelOne()),this, SLOT(endLevelOne()));

}

void MainWindow::loadFileLevelTwo() {

     intro->stop();
     //music for level start here
     startButton->close();
     quitButton->close();
     levelTwo = new LevelTwo(scrollx,scrolly);
     view->setStyleSheet("background-image: url(:images/levelClear2.png)");
     view->setScene(levelTwo);
     connect(this->levelTwo, SIGNAL(endLevelTwo()),this, SLOT(endLevelTwo()));
}

void MainWindow::loadFileLevelThree() {

    intro->stop();
    //music for level start here
    startButton->close();
    quitButton->close();
    levelThree = new LevelThree(scrollx,scrolly);
    view->setScene(levelThree);
    view->setStyleSheet("background-image: url(:images/levelClear3.png)");
    connect(this->levelThree, SIGNAL(endLevelThree()),this, SLOT(endLevelThree()));

}

void MainWindow::loadFileLevelFour() {

    intro->stop();
    //music for level start here
    startButton->close();
    quitButton->close();
    levelFour = new LevelFour(scrollx,scrolly);
    view->setScene(levelFour);
    view->setStyleSheet("background-image: url(:images/levelClear4.png)");
    connect(this->levelFour, SIGNAL(endLevelFour()),this, SLOT(endLevelFour()));
}

void MainWindow::loadFileLevelFive() {

    intro->stop();
    //music for level start here
    startButton->close();
    quitButton->close();
    levelFive = new LevelFive(scrollx,scrolly);
    view->setScene(levelFive);
    view->setStyleSheet("background-image: url(:images/levelClear5_2.png)");
    connect(this->levelFive, SIGNAL(endLevelFive()),this, SLOT(endLevelFive()));

}

void MainWindow::loadFileLevelSix() {
    /*
    intro->stop();
    //music for level start here
    startButton->close();
    quitButton->close();
    */

    //No level six right now
     qApp->quit();
}

void MainWindow::on_actionDevelopers_triggered() {

    aboutDialog = new AboutDialog();
    aboutDialog->exec();
}
