#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logoanimation.h"
#include "logoanimation.h"
#include "aboutdialog.h"
#include "thread.h"
#include "gear.h"
#include "statusone.h"
#include "optionsdialog.h"
#include "warningdialog.h"
#include "abortwarningdialog.h"
#include "singlescanthread.h"
#include <QPainter>
#include<QDebug>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(650,416);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,641,171);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    threatText = new StatusOne(QPixmap(":images/threatText"));
    threatText->setPos(140,150);
    scene->addItem(threatText);

    mainLogo = new StatusOne(QPixmap(":images/logo2.png"));
    mainLogo->setPos(140,8);
    scene->addItem(mainLogo);
    checkTextOne = false;
    checkTextTwo = false;
    stopMouseMovement = false;

}

MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::startAnimation() {

    ui->label_2->close();
    logo = new LogoAnimation();
    logo->setPos(25, 8);
    scene->addItem(logo);
}

void MainWindow::startGearAnimation() {

    gear = new Gear();
    gear->setPos(330, 60);
    scene->addItem(gear);
}

void MainWindow::on_smartScanButton_clicked() {

    stopMouseMovement = true;
    if(!checkTextOne){

        ui->listWidget->clear();
        QStringList list;
        list<< "C:/";

        QFile inputFile(":/data/viruslist.txt");
        if (inputFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&inputFile);

            QStringList virusList;
            while (!in.atEnd()) {

                QString line = in.readLine();
                virusList << line;
            }
            inputFile.close();
        thread = new Thread(list,virusList);
        connect(thread, &Thread::scanStart, this, &MainWindow::handleScanStart);
        connect(thread, &Thread::scanComplete, this, &MainWindow::handleScanComplete);
        connect(thread, &Thread::infectedFiles, this, &MainWindow::displayInfectedFiles);
        connect(thread, &Thread::finished, thread, &QObject::deleteLater);
        thread->stopThread = false;
        thread->start();

        startAnimation();
        startGearAnimation();

        if(checkTextTwo){
            delete textTwo;
            checkTextTwo = false;
        }
        }
    }
    else{

        warningDialog = new WarningDialog();
        warningDialog->setWindowFlags(Qt::FramelessWindowHint);
        warningDialog->exec();
    }
}

void MainWindow::on_scanSingleFile_clicked() {

    stopMouseMovement = true;
    if(!checkTextOne){

        ui->listWidget->clear();
        QString file = QFileDialog::getOpenFileName(this, tr("Select Directory"), "C:/");
        QFileInfo fi(file);
        QString name = fi.fileName();
        //QFile inputFile("C:/Users/Desktop/Genome/viruslist.txt");
        QFile inputFile(":/data/viruslist.txt");
        if (inputFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&inputFile);

            QStringList virusList;
            while (!in.atEnd()) {

                QString line = in.readLine();
                virusList << line;
            }

            inputFile.close();
            singleScanThread = new SingleScanThread(virusList,name,file);
            connect(singleScanThread, &SingleScanThread::scanStart, this, &MainWindow::handleScanStart);
            connect(singleScanThread, &SingleScanThread::scanComplete, this, &MainWindow::handleScanComplete);
            connect(singleScanThread, &SingleScanThread::infectedFiles, this, &MainWindow::displayInfectedFiles);
            connect(singleScanThread, &SingleScanThread::finished, singleScanThread, &QObject::deleteLater);
            singleScanThread->stopSingleThread = false;
            singleScanThread->start();
            startAnimation();
            startGearAnimation();

            if(checkTextTwo){
                delete textTwo;
                checkTextTwo = false;
            }
        }
    }
    else{

        warningDialog = new WarningDialog();
        warningDialog->setWindowFlags(Qt::FramelessWindowHint);
        warningDialog->exec();
    }
}

void MainWindow::on_scanDirectory_clicked() {

    stopMouseMovement = true;
    if(!checkTextOne){

        QString file = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        ui->listWidget->clear();
        QStringList list;
        list<< file;

        if(file.isEmpty()){
            return;
        }

        QFile inputFile(":/data/viruslist.txt");
        if (inputFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&inputFile);

            QStringList virusList;
            while (!in.atEnd()) {

                QString line = in.readLine();
                virusList << line;
            }
            inputFile.close();
        thread = new Thread(list,virusList);
        connect(thread, &Thread::scanStart, this, &MainWindow::handleScanStart);
        connect(thread, &Thread::scanComplete, this, &MainWindow::handleScanComplete);
        connect(thread, &Thread::infectedFiles, this, &MainWindow::displayInfectedFiles);
        connect(thread, &Thread::finished, thread, &QObject::deleteLater);
        thread->stopThread = false;
        thread->start();

        startAnimation();
        startGearAnimation();

        if(checkTextTwo){
            delete textTwo;
            checkTextTwo = false;
        }
        }
    }
    else{
        warningDialog = new WarningDialog();
        warningDialog->setWindowFlags(Qt::FramelessWindowHint);
        warningDialog->exec();
    }
}

void MainWindow::handleScanStart() {

    textOne = new StatusOne(QPixmap(":images/textOne"));
    textOne->setPos(80,90);
    scene->addItem(textOne);
    checkTextOne = true;
}

void MainWindow::handleScanComplete() {

    delete logo;
    delete gear;
    delete textOne;
    checkTextOne = false;
    textTwo = new StatusOne(QPixmap(":images/textTwo"));
    textTwo->setPos(79,92);
    scene->addItem(textTwo);
    checkTextTwo =  true;
    ui->label_2->show();

    if(ui->listWidget->count()== 0){
        ui->listWidget->addItem("No Threats Detected");
    }
}

void MainWindow::stopThread() {

    thread->stopThread = true;

    delete logo;
    delete gear;
    delete textOne;
    checkTextOne = false;
    textTwo = new StatusOne(QPixmap(":images/textTwo"));
    textTwo->setPos(79,92);
    scene->addItem(textTwo);
    checkTextTwo =  true;
    ui->label_2->show();
}

void MainWindow::on_abort_clicked() {
    stopMouseMovement = true;
    if(checkTextOne){
        abortWarningDialog = new AbortWarningDialog();
        connect(abortWarningDialog, &AbortWarningDialog::stopThread, this, &MainWindow::stopThread);
        abortWarningDialog->setWindowFlags(Qt::FramelessWindowHint);
        abortWarningDialog->exec();
    }
    else{

        return;
    }
}

void MainWindow::on_removeSelectedFile_clicked() {

    stopMouseMovement = true;
    if(ui->listWidget->count()==0) {

        return;
    }
    else if(checkTextOne) {

        return;
    }
    else{

        QString fileToRemove = ui->listWidget->currentItem()->text();
        //QFile::setPermissions(ui->listWidget->currentItem()->text(),QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner);
        QFile::remove(fileToRemove);
        ui->listWidget->takeItem(ui->listWidget->currentRow());
        ui->listWidget->addItem("Item successfully removed");
    }
}



void MainWindow::on_removeAllFiles_clicked() {

    stopMouseMovement = true;
    if(ui->listWidget->count()==0) {

        return;
    }
    else if(checkTextOne) {

        return;
    }
    else{

        QString allItemsInOneString;
        int items = ui->listWidget->count();
        for(int i = 0; i < items; i++) {

            allItemsInOneString += ui->listWidget->item(i)->text();
        }

        QStringList allItemsAsAList;
        int itemsList = ui->listWidget->count();

        for(int i = 0; i < itemsList; i++) {
            allItemsAsAList << ui->listWidget->item(i)->text();
        }

        foreach(QString itemsToDelete,allItemsAsAList){
            QFile::remove(itemsToDelete);
        }

        ui->listWidget->clear();
        ui->listWidget->addItem("All item successfully removed");
    }
}

void MainWindow::on_actionAbout_triggered() {
    stopMouseMovement = true;
    aboutDialog = new AboutDialog();
    aboutDialog->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
    aboutDialog->exec();
}

void MainWindow::on_actionClose_triggered() {

    qApp->quit();
}

void MainWindow::displayInfectedFiles(QString files) {

    QString infectedFiles = files;
    ui->listWidget->addItem(infectedFiles);
}

void MainWindow::on_actionMinimize_triggered() {

   stopMouseMovement = true;
   MainWindow::showMinimized();
}

void MainWindow::on_actionOptions_triggered() {

    stopMouseMovement = true;
    optionsDialog = new OptionsDialog();
    optionsDialog->setWindowFlags(Qt::FramelessWindowHint);
    optionsDialog->exec();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    stopMouseMovement = false;
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {

    if (stopMouseMovement){
        return;
    }else{

    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
    }
}


void MainWindow::on_removeSelectedFile_released() {

    stopMouseMovement = true;
}

void MainWindow::on_removeAllFiles_released() {

    stopMouseMovement = true;
}

void MainWindow::on_abort_released() {

    stopMouseMovement = true;
}

void MainWindow::on_smartScanButton_released() {

    stopMouseMovement = true;
}

void MainWindow::on_scanSingleFile_released() {

    stopMouseMovement = true;
}

void MainWindow::on_scanDirectory_released() {

    stopMouseMovement = true;
}

void MainWindow::on_actionOptions_hovered() {

   stopMouseMovement = true;
}

void MainWindow::on_actionAbout_hovered() {

    stopMouseMovement = true;
}

void MainWindow::on_actionMinimize_hovered() {

    stopMouseMovement = true;
}

void MainWindow::on_actionClose_hovered() {

    stopMouseMovement = true;
}
