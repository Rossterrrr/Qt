#include "predatoralien.h"
#include <QPainter>

PredatorAlien::PredatorAlien(QRectF platformRect, int direction, QGraphicsItem *parent): QGraphicsItem(parent), mCurrentFrame(), mPlatform(platformRect), mDirection(direction) {

    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/pr.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void PredatorAlien::nextFrame() {

    mCurrentFrame += 70;
    if (mCurrentFrame >= 420) {
        mCurrentFrame = 0;
    }

    if(this->pos().x() < mPlatform.x() || this->pos().x() > mPlatform.x()+ mPlatform.width()) {
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (mDirection*7), this->pos().y());
}

QRectF PredatorAlien::boundingRect() const {
    return QRectF(0,0,70,110);
}

void PredatorAlien::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,70, 110);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int PredatorAlien::type() const {
    return Type;
}
