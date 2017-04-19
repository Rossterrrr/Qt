#include "warningdialog.h"
#include "ui_warningdialog.h"

WarningDialog::WarningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarningDialog)
{
    ui->setupUi(this);
}

WarningDialog::~WarningDialog()
{
    delete ui;
}

void WarningDialog::on_pushButton_clicked()
{
    WarningDialog::close();
}

void WarningDialog::mousePressEvent(QMouseEvent *event) {

    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();

}

void WarningDialog::mouseMoveEvent(QMouseEvent *event) {

    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);

}
