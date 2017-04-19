#include "thread.h"
#include <QDebug>

Thread::Thread(QStringList list, QThread *parent) : QThread(parent),m_scanType(list) {

}

void Thread::run() {

    emit scanStart();
    foreach (QString element, m_scanType) {
        QDirIterator directory(element, QDirIterator::Subdirectories);
        while (directory.hasNext()) {
            if(!stopThread){
                directory.next();
                if(QFileInfo(directory.filePath()).suffix() == "pdf") {
                    emit infectedFiles(directory.filePath());
                }
            }
        }
    }
    emit scanComplete();
}




