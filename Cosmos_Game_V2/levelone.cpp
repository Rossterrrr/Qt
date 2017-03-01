/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Carl Sagan Video Game
*/

#include  "levelone.h"
#include <QKeyEvent>
#include <QScrollBar>
#include <QPropertyAnimation>
//#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <typeinfo>
#include "player.h"
#include "backgrounditem.h"
#include "platform.h"
#include "ground.h"
#include "parallaxlayerone.h"
#include "alien.h"
#include "path.h"
#include "bullet.h"


LevelOne::LevelOne(QScrollBar*s , QObject *parent) : QGraphicsScene(0,0,0,0, parent)
  , m_velocity(7)
  , m_skippedMoving(0)
  , m_groundLevel(0)
  //, m_minX(0)
  //, m_maxX(0)
  , m_jumpAnimation(new QPropertyAnimation(this))
  , m_jumpHeight(200)
  , m_fieldWidth()//width of the level
  , m_player(0)
  , m_Background(0)
  , m_Scene(0)
  , m_platform()
  , scroll(s)
  ,alien(0)

{
    initPlayField();

    //Timer to check if player is moving
    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &LevelOne::movePlayer);

    //Timer to control player fall speed
    mFallTimer.setInterval(20);
    connect(&mFallTimer, &QTimer::timeout, this, &LevelOne::fallPlayer);

   // bulletTimer.setInterval(20);
   // connect(&bulletTimer, &QTimer::timeout, this, &LevelOne::collisionTimer);

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);
    connect(this, &LevelOne::jumpFactorChanged, this, &LevelOne::jumpPlayer);
    connect(m_jumpAnimation, &QPropertyAnimation::stateChanged, this, &LevelOne::jumpStatusChanged);

     m_player->stand();
}

//Player key movements
void LevelOne::keyPressEvent(QKeyEvent *event) {

    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_Right:
        m_player->addDirection(1);
        m_player->addStandingDirection(1);
        checkTimer();
        break;
    case Qt::Key_Left:
        m_player->addDirection(-1);
        m_player->addStandingDirection(-1);
        checkTimer();
        break;
    case Qt::Key_F:

        m_player->jump();
        bullet = new Bullet(1,m_player->standingDirection());
        if(m_player->standingDirection() == -1){
            bullet->setPos(m_player->pos().x(),  m_player->pos().y()+15);
        }
        else {
            bullet->setPos(m_player->pos().x()+110,  m_player->pos().y()+15);

        }
         addItem(bullet);
         //bulletTimer.start();

        break;
    case Qt::Key_Space:
        if (QAbstractAnimation::Stopped == m_jumpAnimation->state()) {
            m_jumpAnimation->start();
        }
        break;
    default:
        break;
    }
}

void LevelOne::keyReleaseEvent(QKeyEvent *event) {
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
    case Qt::Key_F:
        //qDebug() << "F released";
        if (0 == m_player->direction()) {
            m_player->stand();

        }

         break;
        //    case Qt::Key_Space:
        //        return;
        //        break;
    default:
        break;
    }
}

void LevelOne::collisionTimer() {


    //checkCollidingAlien();
}

void LevelOne::movePlayer() {



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
        if(m_player->pos().x()>=7600){
            return;
         }
        m_player->moveBy(dx, 0);
        int diff = m_player->pos().x() - scroll->value();

        if(scroll->value() >= 7200 ){
                    return;

                }

        if(diff > 800) {
            scroll->setValue(dx + scroll->value());
            m_Background->setPos(dx + m_Background->pos().x(), 0);
           // m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
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
            //m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
        }
    }
    sendSignal();
}

void LevelOne::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) {
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running) {
    }
}



//Make player detect other platform when falling
void LevelOne::fallPlayer() {

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
void LevelOne::jumpPlayer() {

   // checkCollidingAlien();

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
void LevelOne::initPlayField() {

    setSceneRect(0,0,8000,760);

    m_groundLevel = 660;

    //add
    m_Background = new BackgroundItem(QPixmap(":images/stars"));
    addItem(m_Background);

    parallaxLayerOne =  new ParallaxLayerOne(1);
    parallaxLayerOne ->setPos(0, m_groundLevel - parallaxLayerOne->boundingRect().height() +200);
    addItem(parallaxLayerOne);

    p1 = new Platform(4);
    p1->setPos(400, m_groundLevel - p1->boundingRect().height() -175);
    addItem(p1);

    p2 = new Platform(5);
    p2->setPos(700, m_groundLevel - p2->boundingRect().height() -375);
    addItem(p2);

    //Path for alien
    pathOne = new Path(3);
    pathOne->setPos(400, m_groundLevel - pathOne->boundingRect().height() -175);
    addItem(pathOne);

    //Add Alien
    alien = new Alien(QRectF(pathOne->pos(), pathOne->boundingRect().size()), -1);
    alien->setPos(500, m_groundLevel - alien->boundingRect().height()-225);
    addItem(alien);
    startTimer(100);

    alien2 = new Alien(QRectF(p2->pos(), p2->boundingRect().size()), -1);
    alien2->setPos(700, m_groundLevel - alien->boundingRect().height()-425);
    addItem(alien2);

    ground0 = new Ground(6);
    ground0->setPos(0, 660);
    addItem(ground0);

    //add player
    m_player = new Player();
    m_player->setPos(10, ground0->pos().y() - m_player->boundingRect().height());
    addItem(m_player);

  //checkCollidingAlien();


//handleCollisionWithPlatform();
}

//Timer event for animations
void LevelOne::timerEvent(QTimerEvent *) {
alien->nextFrame();
alien2->nextFrame();
//bullet->nextFrame();
//bullet->nextFrame();
//checkCollidingAlien();
//checkCollidingAlien();
}

qreal LevelOne::jumpFactor() const{
    return m_jumpFactor;
}

void LevelOne::setJumpFactor(const qreal &jumpFactor) {
    if (m_jumpFactor == jumpFactor)
        return;

    m_jumpFactor = jumpFactor;
    emit jumpFactorChanged(m_jumpFactor);
}

void LevelOne::sendSignal()
{

    if(m_player->pos().x()>=7500){

    emit endLevelOne();
    }
}

//Check timer and change player to standing position if timer stopped
void LevelOne::checkTimer(){
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

QGraphicsItem* LevelOne::collidingPlatforms() {
    QList<QGraphicsItem*> items =  collidingItems(m_player);
    foreach(QGraphicsItem *item, items) {
        if(Platform *platforms = qgraphicsitem_cast<Platform *>(item)) {
            return platforms;
        }
        if(Ground *ground = qgraphicsitem_cast<Ground *>(item)) {
                    return ground;
                }
    }
    return 0;

}

//Platform collision detection
bool LevelOne::handleCollisionWithPlatform() {
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


void LevelOne::checkCollidingAlien() {

   // QList<QGraphicsItem*> items = collidingItems(alien);
    //foreach (QGraphicsItem* item, items) {

      //  Bullet *a = qgraphicsitem_cast<Bullet*>(item);
       // if(a){

            //removeItem(a);
            //removeItem(alien);
            //delete alien;
            //qDebug() << "Alien Removed";

      //  }
   // }
}
