#include "thread.h"
#include <QDebug>

//Scan files
void Thread::run() {

    QDirIterator directory("C:/", QDirIterator::Subdirectories);

    for(int i =1; i<1000000000; i++) {
        //qDebug()<<i;
        directory.next();
        //qDebug()<<directory.next();
        if(QFileInfo(directory.filePath()).suffix() == "troj") {
            emit resultTwo(directory.filePath());
            //qDebug()<<directory.filePath();
        }
        if(directory.hasNext()){
            i++;
        }else{
            emit result("Scan Complete");
            return;
        }
    }
}

//qDebug() << directory.next();
//-------------------------------------------------Working----------------------//
/*
    QDirIterator directory("G:/", QDirIterator::Subdirectories);

    while(directory.hasNext()){

        if(QFileInfo(directory.filePath()).suffix() == "troj"){

            emit resultTwo(directory.filePath());
        }
        directory.next();
    }
*/



/*
    for(int i=0; i < 100000; i++){

        if (directory.hasNext()) {
                directory.next();
            if (QFileInfo(directory.filePath()).isFile()){
                if (QFileInfo(directory.filePath()).suffix() == "troj"){
                    qDebug()<<directory.filePath();
                    emit resultTwo(directory.filePath());

                }
            }
//qDebug()<<count;
            //total = i;
            //directory.next();

            emit result(QString::number(i+1));
            i++;

            qDebug()<<directory.next();
        }
    }
    */


//if (!directory.hasNext()) {
// stopped = true;
// }
//qDebug()<<directory.next();
//ui->progressBar->setValue(i/980);
//label->setText(QString::number(i));
//emit result(QString::number(i));


