#include "singlescanthread.h"
#include <QDebug>

SingleScanThread::SingleScanThread(QStringList list, QString fileToScan,QString fileLocation, QThread *parent) : QThread(parent)

  ,virusList(list)
  ,passFileToScan(fileToScan)
  ,location(fileLocation)
{

}

void SingleScanThread::run() {

    emit scanStart();

    foreach (const QString &str, virusList) {
        if(!stopSingleThread){
            if (str.contains(passFileToScan)) {
                emit infectedFiles(location);
            }
        }
    }
    emit scanComplete();
}



