#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QObject>
#include <QDirIterator>

class Thread : public QThread

{
    Q_OBJECT

public:
    Thread(QStringList, QStringList, QThread *parent = 0);
    void run();
    bool stopThread;

signals:
    void scanStart();
    void scanComplete();
    void infectedFiles(QString);

public slots:

private:
    QStringList directories;
    QStringList virusList;
    //QString location;
};

#endif // THREAD_H
