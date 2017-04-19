/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#include "bullet.h"
#include "levelone.h"
#include "alien.h"
#include"predatoralien.h"
#include <QPainter>
#include <QGraphicsScene>
#include <typeinfo>


Bullet::Bullet(int standingDirection, QGraphicsItem *parent): QGraphicsItem(parent)

  , mCurrentFrame()
  , m_StandingDirection(standingDirection)

{
    //setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/bullet.png");

    // Create timer for the bullet movement and connect the timer signal to the moveBullet slot
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moveBullet()));
    timer->start(100);
}

void Bullet::moveBullet() {

    if(m_StandingDirection == -1){
        setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        setPos(this->pos().x() + (m_StandingDirection*50), this->pos().y());
    }
    else if(m_StandingDirection == 1){
        setPos(this->pos().x() + (m_StandingDirection*50), this->pos().y());
    }
    else{
        setPos(this->pos().x() + ( m_StandingDirection*50), this->pos().y());
    }

    //Collision Detection
    QList<QGraphicsItem *> colliding_items = collidingItems();

    //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Alien)){

            // remove bullet and alien from the scene but, they are still on the heap
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            emit increaseTheScore(1);


            delete colliding_items[i]; //deleting the aliens causes segmentation fault
            qDebug()<<"Alien deleted";
            delete this;

            // return (all code below refers to bullet that goes beyond level)
            return;

        }
    }
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(PredatorAlien)){

            // remove bullet and alien from the scene but, they are still on the heap
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            delete colliding_items[i]; //deleting the aliens causes segmentation fault
            qDebug()<<"Alien deleted";
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

QRectF Bullet::boundingRect() const {
    return QRectF(0,0,46,20);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,46, 20);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int Bullet::type() const {

    return Type;
}
