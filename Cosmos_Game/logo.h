/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Carl Sagan Video Game
*/

#ifndef LOGO_H
#define LOGO_H

#include <QGraphicsItem>
#include <QPixmap>

class Logo: public QGraphicsItem
{
public:
    enum { Type = UserType + 1};
    Logo(QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:

    int mCurrentFrame;
    QPixmap mPixmap;

};
#endif // LOGO_H
