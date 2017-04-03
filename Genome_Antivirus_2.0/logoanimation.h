#ifndef LOGOANIMATION_H
#define LOGOANIMATION_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QThread>

class LogoAnimation : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 1};
    LogoAnimation(QGraphicsItem *parent = 0);
    void doSetup(QThread &cThread);
    //void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
     void nextFrame();
private:

    int mCurrentFrame7;
    QPixmap mPixmap7;

};
#endif // LOGOANIMATION_H
