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
    void scanStart(int);
    void scanComplete(int);
    void infectedFiles(QString data);

private:

};

#endif // THREAD_H
