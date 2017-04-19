#include "pod.h"
#include <QPainter>

Pod::Pod(int length, QGraphicsItem *parent) :QGraphicsItem(parent),mCurrentFrame(0), mLength(length) {

    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/alienpodu");
}

void Pod::nextFrame() {
    //mCurrentFrame += 0;
    //if (mCurrentFrame >= 0 ) {
       // mCurrentFrame = 0;
   // }
}

QRectF Pod::boundingRect() const {
    return QRectF(0,0,239*mLength,137);
}

void Pod::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 239*mLength; ++i) {
    painter->drawPixmap(i*239,0, mPixmap, mCurrentFrame, 0,239, 137);
    }
    setTransformOriginPoint(boundingRect().center());
}

int Pod::type() const {
    return Type;
}
