#ifndef SINGLESCANTHREAD_H
#define SINGLESCANTHREAD_H

#include <QThread>
#include <QObject>
#include <QFileDialog>
#include <QStringListIterator>

class SingleScanThread : public QThread

{
    Q_OBJECT

public:
    SingleScanThread(QStringList, QString ,QString , QThread *parent = 0);
    void run();
    bool stopSingleThread;

signals:
    void scanStart();
    void scanComplete();
    void infectedFiles(QString);

public slots:

private:
    QStringList virusList;
    QString passFileToScan;
    QStringList alist;
    QString location;

};

#endif // SINGLESCANTHREAD_H
