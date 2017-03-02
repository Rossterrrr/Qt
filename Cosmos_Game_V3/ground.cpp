/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#include "ground.h"
#include <QPainter>

Ground::Ground(int length, QGraphicsItem *parent) :QGraphicsItem(parent),mCurrentFrame(0), mLength(length) {

    //setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/ground1");
}

void Ground::nextFrame() {
    //mCurrentFrame += 0;
    //if (mCurrentFrame >= 0 ) {
       // mCurrentFrame = 0;
   // }
}

QRectF Ground::boundingRect() const {
    return QRectF(0,0,1310*mLength,100);
}

void Ground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 1310*mLength; ++i) {
    painter->drawPixmap(i*1310,0, mPixmap, mCurrentFrame, 0,1310, 100);
    }
    setTransformOriginPoint(boundingRect().center());
}

int Ground::type() const {
    return Type;
}
