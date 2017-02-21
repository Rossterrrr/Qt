/*
 * Author: Jonathan Baird
 * Date: 1/29/2017
 * Purpose: MVC SEC Video Game Punk Rift
*/


#include "optionswindow.h"
#include "ui_optionswindow.h"

OptionsWindow::OptionsWindow(QWidget *parent) :QDialog(parent,Qt::FramelessWindowHint), ui(new Ui::OptionsWindow) {

    ui->setupUi(this);
    //this->setFocusPolicy(Qt::NoFocus);

}

OptionsWindow::~OptionsWindow() {

    delete ui;
}

//Exit the game
void OptionsWindow::on_pushButton_2_clicked() {

    qApp->quit();

}

//close button
void OptionsWindow::on_pushButton_clicked() {

    //OptionsWindow::reject();
    OptionsWindow::close();
    //OptionsWindow::clearFocus();

}

void OptionsWindow::mousePressEvent(QMouseEvent *event) {

    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();

}

void OptionsWindow::mouseMoveEvent(QMouseEvent *event) {

    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);

}
