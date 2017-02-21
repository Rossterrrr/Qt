/*
 * Author: Jonathan Baird
 * Date: 1/29/2017
 * Purpose: MVC SEC Video Game Punk Rift
*/

#include "logo.h"
#include <QPainter>

Logo::Logo(QGraphicsItem *parent) : QGraphicsItem(parent) ,mCurrentFrame()

{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/p.png");

}

void Logo::nextFrame(){

    mCurrentFrame += 1278;
    if (mCurrentFrame >= 28104 ) {
        mCurrentFrame = 0;

    }
}

QRectF Logo::boundingRect() const {
    return QRectF(0,0,1280,760);

}

void Logo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,1280, 760);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int Logo::type() const {
    return Type;
}
