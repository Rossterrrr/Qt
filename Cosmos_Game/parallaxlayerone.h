#ifndef PARALLAXLAYERONE_H
#define PARALLAXLAYERONE_H

#include <QGraphicsItem>
#include <QPixmap>

class ParallaxLayerOne : public QGraphicsItem
{
public:
    enum { Type = UserType + 25 };
    ParallaxLayerOne( int length, QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
    int mDirection;
};
#endif // PARALLAXLAYERONE_H
