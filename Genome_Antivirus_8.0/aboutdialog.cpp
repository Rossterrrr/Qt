#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AboutDialog) {

    ui->setupUi(this);
}

AboutDialog::~AboutDialog() {
    delete ui;
}

void AboutDialog::on_pushButton_clicked() {

    AboutDialog::close();
}

void AboutDialog::mousePressEvent(QMouseEvent *event) {

    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void AboutDialog::mouseMoveEvent(QMouseEvent *event) {

    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}
