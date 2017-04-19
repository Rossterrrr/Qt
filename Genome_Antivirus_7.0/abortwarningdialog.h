#ifndef ABORTWARNINGDIALOG_H
#define ABORTWARNINGDIALOG_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class AbortWarningDialog;
}

class AbortWarningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AbortWarningDialog(QWidget *parent = 0);
    ~AbortWarningDialog();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

signals:
    void stopThread();

private:
    Ui::AbortWarningDialog *ui;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};

#endif // ABORTWARNINGDIALOG_H
