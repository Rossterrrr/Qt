#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent),  ui(new Ui::OptionsDialog) {

    ui->setupUi(this);
}

OptionsDialog::~OptionsDialog() {

    delete ui;
}

void OptionsDialog::mousePressEvent(QMouseEvent *event) {

    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void OptionsDialog::mouseMoveEvent(QMouseEvent *event) {

    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void OptionsDialog::on_pushButton_clicked() {

    OptionsDialog::close();
}
