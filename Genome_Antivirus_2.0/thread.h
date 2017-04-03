#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <Qlabel>
# include <QDirIterator>
#include <QObject>

class Thread : public QThread

{
    Q_OBJECT

public:

    void run();

    signals:
    void result(QString data);
    void resultTwo(QString dataTwo);

private:
    QString messageStr;
    volatile bool stopped;
    QLabel *label;
};

#endif // THREAD_H
