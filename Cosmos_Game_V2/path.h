#ifndef PATH_H
#define PATH_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Path : public QGraphicsItem
{
public:
    enum { Type = UserType + pathType };
    Path ( int length, QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
    //int mDirection;
};

#endif // PATH_H
