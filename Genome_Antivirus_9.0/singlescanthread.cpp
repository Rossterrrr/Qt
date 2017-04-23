#include "singlescanthread.h"
#include <QDebug>
SingleScanThread::SingleScanThread(QStringList list, QString fileToScan,QString fileLocation, QThread *parent) : QThread(parent)

  ,m_scanType(list)
  , passFileToScan(fileToScan)
  ,location(fileLocation) {

}

void SingleScanThread::run() {

    emit scanStart();

    foreach (const QString &str, m_scanType) {
        if(!stopSingleThread){
            if (str.contains(passFileToScan)) {
                emit infectedFiles(location);
            }
        }
    }
    emit scanComplete();
}



