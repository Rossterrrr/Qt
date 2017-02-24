/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Carl Sagan Video Game
*/

#include "levelthree.h"
#include <QKeyEvent>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "player.h"
#include "backgrounditem.h"
#include "platform.h"

LevelThree::LevelThree(QScrollBar*s , QObject *parent) : QGraphicsScene(0,0,0,0, parent)
  , m_velocity(7)
  , m_skippedMoving(0)
  , m_groundLevel(0)
  , m_minX(0)
  , m_maxX(0)
  , m_jumpAnimation(new QPropertyAnimation(this))
  , m_jumpHeight(200)
  , m_fieldWidth()//width of the level
  , m_player(0)
  , m_Background(0)
  , m_Scene(0)
  , m_platform()
  , scroll(s)

{
    initPlayField();

    //Timer to check if player is moving
    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &LevelThree::movePlayer);

    //Timer to controll player fall speed
    mFallTimer.setInterval(20);
    connect(&mFallTimer, &QTimer::timeout, this, &LevelThree::fallPlayer);

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);
    connect(this, &LevelThree::jumpFactorChanged, this, &LevelThree::jumpPlayer);
    connect(m_jumpAnimation, &QPropertyAnimation::stateChanged, this, &LevelThree::jumpStatusChanged);
    //QObject::connect(this, SIGNAL(endLevel()), this->parent(),SLOT());

     m_player->stand();
     qDebug() << "stand activated";
}

//Player key movements
void LevelThree::keyPressEvent(QKeyEvent *event) {

    if (event->isAutoRepeat())
        //qDebug() << "checking auto repeat";
            return;

    switch (event->key()) {
    case Qt::Key_Right:
        qDebug() << " right key";
        m_player->addDirection(1);
        checkTimer();
        break;
    case Qt::Key_Left:
        qDebug() << " left key";
        m_player->addDirection(-1);

        checkTimer();
        break;
    case Qt::Key_Space:
        qDebug() << "space pressed";
        if (QAbstractAnimation::Stopped == m_jumpAnimation->state()) {
            m_jumpAnimation->start();
           // qDebug() << "space pressed; animation start";


            //m_timer.start();
        }
        break;
    default:
        break;
    }
}

void LevelThree::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_Right:
        m_player->addDirection(-1);

        checkTimer();
        break;
    case Qt::Key_Left:
        m_player->addDirection(1);

        checkTimer();
        break;
        //    case Qt::Key_Space:
        //        return;
        //        break;
    default:
        break;
    }
}

void LevelThree::movePlayer() {

    if(m_player->isFalling()){
            return;
        }

    m_player->nextFrame();

    int direction = m_player->direction();
    if (0 == direction)
        return;

    //previously walking on platform, if there is no platform, step down
    if((!(m_platform && m_player->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped)) {
        if(m_platform) {
            m_player->fall();
            mFallTimer.start();
        }
    }

    const int dx = direction * m_velocity;

    if (direction > 0) {
        if(m_player->pos().x()>=1500){
            return;
         }
        m_player->moveBy(dx, 0);
        int diff = m_player->pos().x() - scroll->value();

        if(scroll->value() >= 7400 ){
                    return;

                }

        if(diff > 800) {
            scroll->setValue(dx + scroll->value());
            m_Background->setPos(dx + m_Background->pos().x(), 0);
            m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
        }
    }

    if (direction < 0) {
        if(m_player->pos().x() <= 100){
            return;
        }
        m_player->moveBy(dx, 0);
        int diff = m_player->pos().x() - scroll->value();

        if(diff <  m_player->pos().x()) {
            scroll->setValue(dx + scroll->value());
            m_Background->setPos(dx + m_Background->pos().x(), 0);
            m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
        }
    }
    sendSignalThree();
}

void LevelThree::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) {
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running) {
    }
}

//Make player detect other platform when falling
void LevelThree::fallPlayer() {

    m_player->setPos(m_player->pos().x(), m_player->pos().y() + 30);
    QGraphicsItem* item = collidingPlatforms();
    if(item && handleCollisionWithPlatform()) {

        mFallTimer.stop();
        if (!m_timer.isActive()) {
            m_player->stand();

        }else{
            m_player->walk();
       }
    }

    if((m_player->pos().y() + m_player->boundingRect().height() >= m_groundLevel)){

        m_player->setPos(m_player->pos().x(), m_groundLevel - m_player->boundingRect().height());

        mFallTimer.stop();
        if (!m_timer.isActive()) {
            m_player->stand();

        }else{
             m_player->walk();
        }
        m_platform = 0;
    }
}

//Player jump movement
void LevelThree::jumpPlayer() {

    if (QAbstractAnimation::Stopped == m_jumpAnimation->state()) {

        m_player->stand();
        return;
    }

    QGraphicsItem* item = collidingPlatforms();
    if(item) {
        if(m_player->isTouchingHead(item)) {

            m_jumpAnimation->stop();

            if(m_platform) {
                m_player->setPos(m_player->pos().x(), m_platform->pos().y() - m_player->boundingRect().height());

                return;
            }
            if(!m_platform){
                m_player->setPos(m_player->pos().x(), m_groundLevel - m_player->boundingRect().height());

                return;
            }

        } else {
            if(handleCollisionWithPlatform()) {
                return;
            }
        }
    }

   // qDebug() << "set pos while jumping....";
    qreal y = (m_groundLevel - m_player->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
    if(m_platform) {
        y = (m_platform->pos().y() - m_player->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
        if(!(m_platform && m_player->isTouchingPlatform(m_platform)) && m_jumpFactor < 0.1 ) {
            if(m_player->pos().x() < m_platform->pos().x() || m_player->pos().x() > m_platform->pos().x() + m_platform->boundingRect().width()){
                if(!m_platform){
                m_platform = 0;
                }
                if(m_player->pos().y() < m_groundLevel) {
                    //qDebug() << "Should fall";
                    m_player->fall();
                    mFallTimer.start();
                    return;
                }
            }
        }
    }
    m_player->setPos(m_player->pos().x(), y);
}

//Creating the scene and adding items
void LevelThree::initPlayField() {

    setSceneRect(0,0,8000,760);

    m_groundLevel = 660;

    //add
    m_Background = new BackgroundItem(QPixmap(":images/L3"));
    addItem(m_Background);


    //add ground
    m_ground = new BackgroundItem(QPixmap(":images/g2"));
    addItem(m_ground);
    m_ground->setPos(0, m_groundLevel );

    //add scene image
    m_Scene = new BackgroundItem(QPixmap(":images/Scene"));
    m_Scene->setPos(0, m_groundLevel - m_Scene->boundingRect().height());
    addItem(m_Scene);

   // p1 = new Platform(4);
   // p1->setPos(400, m_groundLevel - p1->boundingRect().height() -150);
   // addItem(p1);

   // p2 = new Platform(5);
   // p2->setPos(650, m_groundLevel - p2->boundingRect().height() -300);
   // addItem(p2);

    //add player
    m_player = new Player();
    //m_minX = m_player->boundingRect().width()/2 ;
    //m_maxX = m_fieldWidth - m_player->boundingRect().width() * 1.5;
    m_player->setPos(10, m_groundLevel - m_player->boundingRect().height());
    //m_realPos = m_minX;
    addItem(m_player);


}

//Timer event for animations
void LevelThree::timerEvent(QTimerEvent *) {

}

qreal LevelThree::jumpFactor() const{
    return m_jumpFactor;
}

void LevelThree::setJumpFactor(const qreal &jumpFactor) {
    if (m_jumpFactor == jumpFactor)
        return;

    m_jumpFactor = jumpFactor;
    emit jumpFactorChanged(m_jumpFactor);
}

void LevelThree::sendSignalThree()
{

    if(m_player->pos().x()>1500){

    emit endLevelThree();
    }
}

//Check timer and change player to standing position if timer stopped
void LevelThree::checkTimer(){
    if (0 == m_player->direction()) {
        m_player->stand();
        m_timer.stop();
    }

    else if (!m_timer.isActive()) {
        m_timer.start();
        m_player->walk();

    }
}

//-------------------------------------------------------------COLLISION DETECTION-----------------------------------------------//

QGraphicsItem* LevelThree::collidingPlatforms() {
    QList<QGraphicsItem*> items =  collidingItems(m_player);
    foreach(QGraphicsItem *item, items) {
        if(Platform *platforms = qgraphicsitem_cast<Platform *>(item)) {
            return platforms;
        }

    }
    return 0;

}

//Platform collision detection
bool LevelThree::handleCollisionWithPlatform() {
    QGraphicsItem* platform =  collidingPlatforms();
    if(platform) {
        QPointF platformPos = platform->pos();
        if(m_player->isTouchingFoot(platform)) {
            m_player->setPos(m_player->pos().x(), platformPos.y() - m_player->boundingRect().height());
            m_platform = platform;
            m_jumpAnimation->stop();
            return true;
        }
    }
    else {
        m_platform = 0;
    }
    return false;
}
