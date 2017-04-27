#include "thread.h"
#include <QDebug>

Thread::Thread(QStringList list, QStringList vList, QThread *parent) : QThread(parent), directories(list),virusList(vList) {

}

void Thread::run() {

    emit scanStart();
    foreach (QString element, directories) {
        QDirIterator directory(element, QDirIterator::Subdirectories);
        while (directory.hasNext()) {
            if(!stopThread){
                directory.next();
                foreach (const QString &str, virusList) {
                    if (directory.fileName() == str){
                        emit infectedFiles(directory.filePath());
                    }
                }
            }
        }
    }
    emit scanComplete();
}




