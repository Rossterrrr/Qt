/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#include "path.h"
#include <QPainter>

Path::Path( int length, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/path.png");
}

void Path::nextFrame() {
   // mCurrentFrame += 48;
    //if (mCurrentFrame >= 768 ) {
      //  mCurrentFrame = 0;
   // }
}

QRectF Path::boundingRect() const {
    return QRectF(0,0,48* mLength,48);
}

void Path::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 48*mLength; ++i) {
        painter->drawPixmap(i*48,0, mPixmap, mCurrentFrame, 0,48, 48);
    }
    setTransformOriginPoint(boundingRect().center());
}

int Path::type() const {
    return Type;
}

