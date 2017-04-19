#ifndef RIGHTEYE_H
#define RIGHTEYE_H
//#include <QGraphicsItem>
//#include <QGraphicsPixmapItem>
#include <QGraphicsObject>
#include <QPixmap>
#include <QTimer>
#include <QObject>
#include "objecttype.h"

class RightEye: public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + rightEyeType };
    RightEye(QGraphicsObject *parent = 0);
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
#endif // RIGHTEYE_H
