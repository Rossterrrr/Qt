#include "abortwarningdialog.h"
#include "ui_abortwarningdialog.h"

AbortWarningDialog::AbortWarningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AbortWarningDialog)
{
    ui->setupUi(this);
}

AbortWarningDialog::~AbortWarningDialog()
{
    delete ui;
}
void AbortWarningDialog::mousePressEvent(QMouseEvent *event) {

    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}

void AbortWarningDialog::mouseMoveEvent(QMouseEvent *event) {

    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

void AbortWarningDialog::on_pushButton_2_clicked() {

    AbortWarningDialog::close();

}

void AbortWarningDialog::on_pushButton_clicked() {

    emit stopThread();
    AbortWarningDialog::close();
}
