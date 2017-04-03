#include "thread.h"
#include <QDebug>

//Scan files
void Thread::run() {

    emit scanStart(1);
    QDirIterator directory("G:/", QDirIterator::Subdirectories);

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




