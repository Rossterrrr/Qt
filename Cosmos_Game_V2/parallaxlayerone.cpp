#include "parallaxlayerone.h"
#include <QPainter>

ParallaxLayerOne::ParallaxLayerOne(int length, QGraphicsItem *parent) :QGraphicsItem(parent),mCurrentFrame(0), mLength(length) {

    //setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/scene2.png");
}

void ParallaxLayerOne::nextFrame() {

    //mCurrentFrame += 0;
    //if (mCurrentFrame >= 0 ) {
       //mCurrentFrame = 0;
   //}
}

QRectF ParallaxLayerOne::boundingRect() const {
    return QRectF(0,0,8000*mLength,780);
}

void ParallaxLayerOne::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 8000*mLength; ++i) {
    painter->drawPixmap(i*8000,0, mPixmap, mCurrentFrame, 0,8000, 780);
    }
    setTransformOriginPoint(boundingRect().center());
}

int ParallaxLayerOne::type() const {
    return Type;
}
