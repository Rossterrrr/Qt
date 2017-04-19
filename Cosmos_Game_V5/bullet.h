/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"
#include <QObject>
#include <QTimer>


class Bullet: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + bulletType };
    Bullet(int standingDirection, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    void handleCollosionWithGoomba();

    signals:
     void increaseTheScore(int);

public slots:
void moveBullet();

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    QRectF mPlatform;    
    int m_StandingDirection;
    int m_CrouchingDirection;



};
#endif // BULLET_H
