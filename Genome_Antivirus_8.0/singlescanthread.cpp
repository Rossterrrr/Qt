#include "singlescanthread.h"
#include <QDebug>
SingleScanThread::SingleScanThread(QStringList list, QString fileToScan, QThread *parent) : QThread(parent),m_scanType(list), passFileToScan(fileToScan) {

}

void SingleScanThread::run() {

    emit scanStart();

    foreach (const QString &str, m_scanType) {

        if (str.contains(passFileToScan)) {
            emit infectedFiles(passFileToScan);
        }
    }

    emit scanComplete();
}



