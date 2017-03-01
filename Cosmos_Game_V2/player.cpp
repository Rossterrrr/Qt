/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Carl Sagan Video Game
*/


#include "player.h"
#include <QDebug>
#include <QPainter>

Player::Player(QGraphicsItem *parent): QGraphicsItem(parent),m_direction(),mCurrentFrame(0), mState(Standing),m_StandingDirection() {


    setFlag(ItemClipsToShape);
    mWalkPixmap = QPixmap(":images/s10.png");
    mStandingPixmap = QPixmap(":images/playerstop.png");
    mJumpPixmap = QPixmap(":images/shoot.png");
    mPixmap = mWalkPixmap;
}

Player::~Player(){

}

void Player::stand() {
    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;


}

void Player::jump() {
    mPixmap = mJumpPixmap;
    mCurrentFrame = 0;
    mState = Jumping;
}

void Player::walk() {
    //qDebug() << "Walking..";
    if(mState == Walking) {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;
}

void Player::fall() {
    mState = Falling;
}

bool Player::isFalling() {
    return mState == Falling;
}

int Player::direction() const {
    return m_direction;
}

int Player::standingDirection() const
{
    return m_StandingDirection;
}

void Player::nextFrame() {
    mCurrentFrame += 153;
    if (mCurrentFrame >= 2907) {
        mCurrentFrame = 0;
    }
}

QRectF Player::boundingRect() const {
    return QRectF(0,0,160,160);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,160, 160);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

void Player::addDirection(int direction) {

    if (direction == m_direction)
        return;

    m_direction += direction;

    if (0 != m_direction) {
        if (-1 == m_direction)
            //QTransform matrix flips the image to face the other direction if left key is pressed
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else//moving right restore normal state by assigning an empty Qtransform object which is an idetntity matrix
            setTransform(QTransform());
    }
}

void Player::addStandingDirection(int standingDirection)
{
     m_StandingDirection = standingDirection;
}

bool Player::isTouchingFoot(QGraphicsItem *item) {

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool Player::isTouchingHead(QGraphicsItem *item) {

    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());   
    return rect.intersects(otherRect);
}

bool Player::isTouchingPlatform(QGraphicsItem *item) {
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

