/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#ifndef ALIEN_H
#define ALIEN_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include "objecttype.h"

class Alien: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + alienType };
    Alien(QRectF platformRect, int direction,QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
     void nextFrame();

private:

    int mCurrentFrame;
    QPixmap mPixmap;
    QRectF mPlatform;
    int mDirection;
};
#endif // ALIEN_H
