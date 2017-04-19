#ifndef PREDATORALIEN_H
#define PREDATORALIEN_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include "objecttype.h"

class PredatorAlien: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + PredatorAlienType };
    PredatorAlien(QRectF platformRect, int direction,QGraphicsItem *parent = 0);
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
#endif // PREDATORALIEN_H
