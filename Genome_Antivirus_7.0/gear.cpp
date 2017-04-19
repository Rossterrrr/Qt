#include "gear.h"
#include <QPainter>

Gear::Gear(QGraphicsItem *parent): QGraphicsItem(parent) ,mCurrentFrame7() {

    setFlag(ItemClipsToShape);
    mPixmap7 = QPixmap(":images/dgear15.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void Gear::nextFrame(){

    mCurrentFrame7 += 95;
    if (mCurrentFrame7 >= 4465) {
        mCurrentFrame7 = 0;
    }
}

QRectF Gear::boundingRect() const {

    return QRectF(0,0,95,80);
}

void Gear::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(0,0, mPixmap7, mCurrentFrame7, 0,95, 80);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int Gear::type() const {

    return Type;
}
