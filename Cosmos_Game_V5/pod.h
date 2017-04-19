#ifndef POD_H
#define POD_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Pod : public QGraphicsItem
{
public:
    enum { Type = UserType + podType};
    Pod( int length, QGraphicsItem *parent = 0);
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
#endif // POD_H
