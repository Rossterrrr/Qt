#include "rock.h"
#include <QPainter>

Rock::Rock(int length, QGraphicsItem *parent) :QGraphicsItem(parent),mCurrentFrame(0), mLength(length) {

    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/rock");
}

void Rock::nextFrame() {
    //mCurrentFrame += 0;
    //if (mCurrentFrame >= 0 ) {
       // mCurrentFrame = 0;
   // }
}

QRectF Rock::boundingRect() const {
    return QRectF(0,0,214*mLength,353);
}

void Rock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 214*mLength; ++i) {
    painter->drawPixmap(i*214,0, mPixmap, mCurrentFrame, 0,214, 353);
    }
    setTransformOriginPoint(boundingRect().center());
}

int Rock::type() const {
    return Type;
}
