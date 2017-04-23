#ifndef WARNINGDIALOG_H
#define WARNINGDIALOG_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class WarningDialog;
}

class WarningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WarningDialog(QWidget *parent = 0);
    ~WarningDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WarningDialog *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};

#endif // WARNINGDIALOG_H
