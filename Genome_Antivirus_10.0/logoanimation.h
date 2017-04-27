#ifndef LOGOANIMATION_H
#define LOGOANIMATION_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>


class LogoAnimation : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 1};
    LogoAnimation(QGraphicsItem *parent = 0);

    //void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    QTimer *timer;

public slots:
     void nextFrame();

private:

    int mCurrentFrame7;
    QPixmap mPixmap7;
    //QTimer *timer;

};
#endif // LOGOANIMATION_H
