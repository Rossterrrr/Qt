/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#include  "levelone.h"
#include <QKeyEvent>
#include <QScrollBar>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include "player.h"
#include "backgrounditem.h"
#include "platform.h"
#include "ground.h"
#include "parallaxlayerone.h"
#include "alien.h"
#include "path.h"
#include "bullet.h"
#include "righteye.h"
#include "lefteye.h"
#include "predatoralien.h"
#include "rock.h"
#include "pod.h"
#include "score.h"


LevelOne::LevelOne(QScrollBar*s , QObject *parent) : QGraphicsScene(0,0,0,0, parent)
  , m_velocity(7)
  , m_skippedMoving(0)
  , m_groundLevel(0)  
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
    connect(&m_timer, &QTimer::timeout, this, &LevelOne::movePlayer);

    //Timer to control player fall speed
    mFallTimer.setInterval(20);
    connect(&mFallTimer, &QTimer::timeout, this, &LevelOne::fallPlayer);

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);
    connect(this, &LevelOne::jumpFactorChanged, this, &LevelOne::jumpPlayer);
    connect(m_jumpAnimation, &QPropertyAnimation::stateChanged, this, &LevelOne::jumpStatusChanged);

    //connect(this->bullet, SIGNAL(increaseTheScore(int)),this, SLOT(scoreIncrease(int)));

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
        m_player->addCrouchingDirection(0);

        checkTimer();
        break;
    case Qt::Key_Left:
        m_player->addDirection(-1);
        m_player->addStandingDirection(-1);
        m_player->addCrouchingDirection(0);
        checkTimer();
        break;
    case Qt::Key_Down:
            m_player->addCrouchingDirection(2);
            m_player->addDirection(0);
        break;
    case Qt::Key_F:

         //If player is NOT moving and facing left and NOT crouching: shoot Left using stand shoot image
        if((m_player->direction() == 0) && (m_player->standingDirection() == -1) && (m_player->crouchingDirection()!=2)){
            bullet = new Bullet(m_player->standingDirection());
            m_player->standShoot();
            bullet->setPos(m_player->pos().x(),  m_player->pos().y()+15);
        }
        //If player is NOT moving and facing right and NOT crouching: shoot right using stand shoot image
        else if((m_player->direction() == 0) && (m_player->standingDirection() != -1) && (m_player->crouchingDirection()!=2)) {
            bullet = new Bullet(1);
            m_player->standShoot();
            bullet->setPos(m_player->pos().x()+110,  m_player->pos().y()+15);
        }
        //If player is moving and facing right and NOT crouching: shoot right using moving image
        else if((m_player->direction() == 1) && ( m_player->standingDirection() != -1) && (m_player->crouchingDirection()!=2)) {
            bullet = new Bullet(1);
            m_player->walk();
            bullet->setPos(m_player->pos().x()+190,  m_player->pos().y()+35);
        }
        //If player is moving and facing left and NOT crouching: shoot left using moving image
        else if((m_player->direction() == -1) && (m_player->standingDirection() == -1) && (m_player->crouchingDirection()!=2)) {
            bullet = new Bullet(m_player->standingDirection());
            m_player->walk();
            bullet->setPos(m_player->pos().x()-70,  m_player->pos().y()+35);
        }
        //If player is NOT moving and facing left and crouching: shoot Left using crouching image: (Handled in PLayer.cpp)
        else if((m_player->direction() == 0) && (m_player->standingDirection() == -1) && (m_player->crouchingDirection()==2)){
            bullet = new Bullet(m_player->standingDirection());
            bullet->setPos(m_player->pos().x() +10,  m_player->pos().y()+55);
        }
        //If player is NOT moving and facing right and crouching: shoot rightusing crouching image: (Handled in PLayer.cpp)
        else if((m_player->direction() == 0) && (m_player->standingDirection() == 1) && (m_player->crouchingDirection()==2)){
            bullet = new Bullet(m_player->standingDirection());
            bullet->setPos(m_player->pos().x()+110,  m_player->pos().y()+55);
        }
        //Add the bullet after a decision has been made
        addItem(bullet);
        connect(this->bullet, SIGNAL(increaseTheScore(int)),this, SLOT(scoreIncrease(int)));

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
    case Qt::Key_Down:
        m_player->addCrouchingDirection(0);
        break;
    case Qt::Key_F:

        if (0 == m_player->direction() && 0 == m_player->crouchingDirection()) {
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

void LevelOne::scoreIncrease(int n) {

    int signal =n;

    if(signal==1){

    m_score->increase();
    }else{

        return ;
    }
}

void LevelOne::movePlayer() {

    checkCollidingRock();

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
            m_weponTypeBox->setPos(dx + m_weponTypeBox->pos().x(), m_weponTypeBox->y());
            m_bulletType->setPos(dx + m_bulletType->pos().x(), m_bulletType->y());
            m_score->setPos(dx + m_score->pos().x(), m_score->y());
        }
    }

    if (direction < 0) {
        if(m_player->pos().x() <= 100){
            return;
        }
        m_player->moveBy(dx, 0);
        int diff = m_player->pos().x() - scroll->value();

        if((diff <  m_player->pos().x())&&(!checkCollidingRock())) {
            scroll->setValue(dx + scroll->value());
            m_Background->setPos(dx + m_Background->pos().x(), 0);
            m_weponTypeBox->setPos(dx + m_weponTypeBox->pos().x(), m_weponTypeBox->y());
            m_bulletType->setPos(dx + m_bulletType->pos().x(), m_bulletType->y());
            m_score->setPos(dx + m_score->pos().x(), m_score->y());
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

    checkCollidingRock();

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

//Create the scene and add items
void LevelOne::initPlayField() {

    //Set scene size
    setSceneRect(0,0,8000,760);

    //Set the ground level
    m_groundLevel = 660;

    //Add Background Image
    m_Background = new BackgroundItem(QPixmap(":images/stars"));
    addItem(m_Background);

    //Add wepon type display box
    m_weponTypeBox =  new BackgroundItem(QPixmap(":images/wepontypebox"));
    m_weponTypeBox->setPos(650, m_groundLevel - m_weponTypeBox->boundingRect().height() -570);
    addItem(m_weponTypeBox);

    //Add bullet type image to wepon type display box
    m_bulletType =  new BackgroundItem(QPixmap(":images/bullet"));
    m_bulletType ->setPos(664, m_groundLevel - m_bulletType ->boundingRect().height() -595);
    addItem(m_bulletType);

    //Add a parallax scrolling lager
    parallaxLayerOne =  new ParallaxLayerOne(1);
    parallaxLayerOne->setPos(0, m_groundLevel - parallaxLayerOne->boundingRect().height() +200);
    addItem(parallaxLayerOne);

    //Add platform
    p1 = new Platform(4);
    p1->setPos(400, m_groundLevel - p1->boundingRect().height() -175);
    addItem(p1);

    //Add platform
    p2 = new Platform(5);
    p2->setPos(700, m_groundLevel - p2->boundingRect().height() -375);
    addItem(p2);

    p3 = new Platform(7);
    p3->setPos(1000, m_groundLevel - p3->boundingRect().height() -275);
    addItem(p3);

    p4 = new Platform(6);
    p4->setPos(1450, m_groundLevel - p4->boundingRect().height() -350);
    addItem(p4);

    //Path for alien
    pathOne = new Path(3);
    pathOne->setPos(400, m_groundLevel - pathOne->boundingRect().height() -175);
    addItem(pathOne);

    pathTwo = new Path(15);
    pathTwo ->setPos(400, m_groundLevel - pathTwo ->boundingRect().height());
    addItem(pathTwo );

    //Add Alien
    alien = new Alien(QRectF(pathOne->pos(), pathOne->boundingRect().size()), -1);
    alien->setPos(500, m_groundLevel - alien->boundingRect().height()-225);
    addItem(alien);
    //startTimer(100);

    //Add alien 2
    alien2 = new Alien(QRectF(p3->pos(), p3->boundingRect().size()), -1);
    alien2->setPos(1000, m_groundLevel - alien->boundingRect().height()-325);
    addItem(alien2);

    //Add predator alien
    //predatorAlien = new PredatorAlien(QRectF(p3->pos(), p3->boundingRect().size()), -1);
   //predatorAlien->setPos(1000, m_groundLevel - alien->boundingRect().height()-325);
    //addItem(predatorAlien);

    predatorAlien2 = new PredatorAlien(QRectF(pathTwo->pos(), pathTwo->boundingRect().size()), -1);
    predatorAlien2->setPos(400, m_groundLevel - alien->boundingRect().height());
    //addItem(predatorAlien2);

    rock = new Rock(1);
    rock->setPos(1500, m_groundLevel - rock->boundingRect().height()+25);
    addItem(rock);

    pod = new Pod(1);
    pod->setPos(705, m_groundLevel - pod->boundingRect().height()-250);
    addItem(pod);

    //Add the ground
    ground0 = new Ground(6);
    ground0->setPos(0, 660);
    addItem(ground0);

    rightEye = new RightEye();
    rightEye->setPos(2550,ground0->pos().y() - rightEye->boundingRect().height()-170);
    addItem(rightEye);

    leftEye = new LeftEye();
    leftEye->setPos(2650,ground0->pos().y() - rightEye->boundingRect().height()-170);
    addItem(leftEye);

    m_score = new Score();
    m_score->setPos(1100, m_groundLevel - m_score->boundingRect().height()-610);
    addItem(m_score);

    //Add player
    m_player = new Player();
    m_player->setPos(10, ground0->pos().y() - m_player->boundingRect().height());
    addItem(m_player);

}

//Timer event for animations if needed
void LevelOne::timerEvent(QTimerEvent *) {


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

// Signal to end the level when player reaches a certain point
void LevelOne::sendSignal() {

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

bool LevelOne::checkCollidingRock() {
    QList<QGraphicsItem*> items = collidingItems(m_player);
    foreach (QGraphicsItem* item, items) {

        Rock* r = qgraphicsitem_cast<Rock*>(item);
        if(r){

            if(r->pos().x()){
                if(m_player->pos().x() < r->pos().x()){
                    m_player->setPos(r->pos().x()- m_player->boundingRect().width(),m_player->pos().y());
                    return true;
                }

                else if(m_player->pos().x() > r->pos().x()){
                    m_player->setPos(r->pos().x() + m_player->boundingRect().width()+50,m_player->pos().y());
                     return true;
                }
                else{
                    return false;
                }
            }
        }
    }
    return false;
}
