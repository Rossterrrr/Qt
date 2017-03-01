#include "bullet.h"
#include "levelone.h"
#include "alien.h"
#include <QPainter>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
Bullet::Bullet( int direction, int standingDirection, QGraphicsItem *parent)
    : QGraphicsItem(parent), mCurrentFrame3(), mDirection(direction), m_StandingDirection(standingDirection)
{
    //setFlag(ItemClipsToShape);
    mPixmap3 = QPixmap(":images/bullet.png");

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));      
    timer->start(100);
}

void Bullet::nextFrame() {

    if(m_StandingDirection == -1){
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
        setPos(this->pos().x() - (mDirection*50), this->pos().y());
    }
    else
        setPos(this->pos().x() + (mDirection*50), this->pos().y());

    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Alien)){

            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

           // delete colliding_items[i]; deleting the aliens causes segmentation fault
            delete this;

            // return (all code below refers to bullet that goes beyond level)
            return;
        }
    }
    if ((pos().x() + boundingRect().width() > 8000)||(pos().x() + boundingRect().width() < 0)){
            scene()->removeItem(this);
            delete this;
            qDebug()<<"bullet deleted";
        }
}

void Bullet::timerEvent(QTimerEvent *)
{

}

QRectF Bullet::boundingRect() const {
    return QRectF(0,0,46,20);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap3, mCurrentFrame3, 0,46, 20);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int Bullet::type() const {
    return Type;
}
