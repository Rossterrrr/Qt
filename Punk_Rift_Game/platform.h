/*
 * Author: Jonathan Baird
 * Date: 1/29/2017
 * Purpose: MVC SEC Video Game Punk Rift
*/

#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsItem>
#include <QPixmap>

class Platform : public QGraphicsItem
{
public:
    enum { Type = UserType + 2 };
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
