/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#include "alien.h"
#include <QPainter>

Alien::Alien(QRectF platformRect, int direction, QGraphicsItem *parent): QGraphicsItem(parent), mCurrentFrame(), mPlatform(platformRect), mDirection(direction) {

    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/alien2.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void Alien::nextFrame() {

    mCurrentFrame += 54;
    if (mCurrentFrame >= 319 ) {
        mCurrentFrame = 0;
    }

    if(this->pos().x() < mPlatform.x() || this->pos().x() > mPlatform.x()+ mPlatform.width()) {
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (mDirection*7), this->pos().y());
}

QRectF Alien::boundingRect() const {
    return QRectF(0,0,50,110);
}

void Alien::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,50, 110);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int Alien::type() const {
    return Type;
}
