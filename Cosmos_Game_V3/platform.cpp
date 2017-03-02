/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#include "platform.h"
#include <QPainter>

Platform::Platform(int length, QGraphicsItem *parent) :QGraphicsItem(parent),mCurrentFrame(0), mLength(length) {

    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/platform");
}

void Platform::nextFrame() {
    //mCurrentFrame += 0;
    //if (mCurrentFrame >= 0 ) {
       // mCurrentFrame = 0;
   // }
}

QRectF Platform::boundingRect() const {
    return QRectF(0,0,50*mLength,50);
}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 50*mLength; ++i) {
    painter->drawPixmap(i*50,0, mPixmap, mCurrentFrame, 0,50, 50);
    }
    setTransformOriginPoint(boundingRect().center());
}

int Platform::type() const {
    return Type;
}
