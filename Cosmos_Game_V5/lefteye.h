#ifndef LEFTEYE_H
#define LEFTEYE_H

#include <QGraphicsObject>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include "objecttype.h"

class LeftEye: public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + leftEyeType };
    LeftEye(QGraphicsObject *parent = 0);
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
#endif // LEFTEYE_H
