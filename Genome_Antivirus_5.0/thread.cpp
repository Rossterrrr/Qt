#include "thread.h"
#include <QDebug>


Thread::Thread(QStringList list, QThread *parent) : QThread(parent),m_scanType(list) {

}

void Thread::run() {

    emit scanStart(1);
    foreach (QString element, m_scanType) {

        QDirIterator directory(element, QDirIterator::Subdirectories);

        for(int i =1; i < 1000000000; i++) {
            directory.next();
            if(QFileInfo(directory.filePath()).suffix() == "troj") {
                emit infectedFiles(directory.filePath());
            }
            if(directory.hasNext()){
                i++;
            }else{
                emit scanComplete(3);
                return;
            }
        }
    }
}




