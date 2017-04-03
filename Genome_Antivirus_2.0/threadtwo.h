#ifndef THREADTWO_H
#define THREADTWO_H
#include <QThread>
#include <Qlabel>
# include <QDirIterator>
#include <QObject>

class ThreadTwo : public QThread

{
    Q_OBJECT

public:

    void run();
    // long running operation
    //emit result("I <3 threads");

    signals:
    //void resultTwo(QString data);

private:
    QString messageStr;
    volatile bool stopped;
    QLabel *label;
};
#endif // THREADTWO_H
