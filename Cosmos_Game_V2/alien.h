#ifndef ALIEN_H
#define ALIEN_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Alien: public QGraphicsItem
{
public:
    enum { Type = UserType + alienType };
    Alien(QRectF platformRect, int direction,QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    //void handleCollosionWithGoomba();
private:

    int mCurrentFrame3;
    QPixmap mPixmap3;
    QRectF mPlatform;
    int mDirection;

};
#endif // ALIEN_H
