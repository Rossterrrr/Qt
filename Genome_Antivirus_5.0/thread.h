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
    Thread(QStringList list,QThread *parent = 0);
    void run();


    signals:
    void scanStart(int);
    void scanComplete(int);
    void infectedFiles(QString data);

public slots:


private:
 QStringList m_scanType;
};

#endif // THREAD_H
