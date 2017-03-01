#include "alien.h"
#include <QPainter>

Alien::Alien(QRectF platformRect, int direction, QGraphicsItem *parent)
    : QGraphicsItem(parent), mCurrentFrame3(), mPlatform(platformRect), mDirection(direction)
{
    setFlag(ItemClipsToShape);
    mPixmap3 = QPixmap(":images/alien2.png");
}

void Alien::nextFrame() {
    mCurrentFrame3 += 54;
    if (mCurrentFrame3 >= 319 ) {
        mCurrentFrame3 = 0;
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
    painter->drawPixmap(0,0, mPixmap3, mCurrentFrame3, 0,50, 110);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int Alien::type() const {
    return Type;
}
