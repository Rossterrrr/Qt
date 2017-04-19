#ifndef ROCK_H
#define ROCK_H
#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Rock : public QGraphicsItem
{
public:
    enum { Type = UserType + rockType};
    Rock( int length, QGraphicsItem *parent = 0);
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
#endif // ROCK_H
