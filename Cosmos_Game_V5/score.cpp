#include "score.h"
#include <QFont>
#include<QFontDatabase>


Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the coinCount to 0
    scoreCount = 0;
/*
    // draw the text
    int id = QFontDatabase::addApplicationFont(":font/nasalization-rg.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(scoreCount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("nasalization-rg",30));
*/
    setPlainText(QString("Score: ") + QString::number(scoreCount)); // Score: 0
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",24));
}

void Score::increase(){
    scoreCount++;
    setPlainText(QString("Score: ") + QString::number(scoreCount * 150));

}

int Score::getScore(){
    return scoreCount;
}
