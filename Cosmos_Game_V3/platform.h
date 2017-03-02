/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Platform : public QGraphicsItem
{
public:
    enum { Type = UserType + platformType};
    Platform( int length, QGraphicsItem *parent = 0);
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
#endif // PLATFORM_H
