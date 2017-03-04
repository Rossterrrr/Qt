#include "lefteye.h"
#include <QPainter>

LeftEye::LeftEye( QGraphicsObject *parent): QGraphicsObject(parent), mCurrentFrame() {

    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/lefteye.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void LeftEye::nextFrame() {

    mCurrentFrame += 56;
    if (mCurrentFrame >= 2288 ) {
        mCurrentFrame = 0;
    }

}

QRectF LeftEye::boundingRect() const {
    return QRectF(0,0,50,30);
}

void LeftEye::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,50, 30);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int LeftEye::type() const {
    return Type;
}
