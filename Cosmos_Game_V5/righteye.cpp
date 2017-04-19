#include "righteye.h"
#include <QPainter>

RightEye::RightEye(QGraphicsObject *parent): QGraphicsObject (parent), mCurrentFrame() {

    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/righteye.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void RightEye::nextFrame() {

    mCurrentFrame += 56;
    if (mCurrentFrame >= 2288 ) {
        mCurrentFrame = 0;
    }

}

QRectF RightEye::boundingRect() const {
    return QRectF(0,0,50,30);
}

void RightEye::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,50, 30);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int RightEye::type() const {
    return Type;
}
