#ifndef GEAR_H
#define GEAR_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>


class Gear : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 2};
    Gear(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
     void nextFrame();
private:

    int mCurrentFrame7;
    QPixmap mPixmap7;

};
#endif // GEAR_H
