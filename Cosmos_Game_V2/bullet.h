#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"
#include <QObject>
#include <QTimer>

class LevelOne;
class Bullet: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + bulletType };
    Bullet( int direction, int standingDirection,QGraphicsItem *parent = 0);

    void timerEvent(QTimerEvent *);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    void handleCollosionWithGoomba();
public slots:
void nextFrame();

private:
    int mCurrentFrame3;
    QPixmap mPixmap3;
    QRectF mPlatform;
    int mDirection;
    int m_StandingDirection;
    QTimer * timer;
};
#endif // BULLET_H
