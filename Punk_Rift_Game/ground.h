#ifndef GROUND_H
#define GROUND_H

#include <QGraphicsItem>
#include <QPixmap>

class Ground : public QGraphicsItem
{
public:
    enum { Type = UserType + 9 };
    Ground( int length, QGraphicsItem *parent = 0);
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
#endif // GROUND_H
