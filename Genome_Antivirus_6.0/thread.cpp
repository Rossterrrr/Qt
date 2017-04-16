#include "thread.h"
#include <QDebug>


Thread::Thread(QStringList list, QThread *parent) : QThread(parent),m_scanType(list) {

}

void Thread::run() {

    emit scanStart(1);
    foreach (QString element, m_scanType) {
        QDirIterator directory(element, QDirIterator::Subdirectories);
        while (directory.hasNext()) {
            directory.next();
            if(QFileInfo(directory.filePath()).suffix() == "troj") {
                emit infectedFiles(directory.filePath());
            }
        }
    }
    emit scanComplete(3);
}




