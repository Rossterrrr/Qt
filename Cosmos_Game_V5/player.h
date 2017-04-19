/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Cosmos Video Game
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPixmap>

class Player : public QGraphicsItem
{
public:

     Player(QGraphicsItem *parent = 0);
     ~Player();
    int direction() const;
    int standingDirection() const;
    int crouchingDirection() const;
    void addDirection(int direction);
    void addStandingDirection(int standingDirection);
    void addCrouchingDirection(int crouchingDirection);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool isTouchingFoot(QGraphicsItem *item);
    bool isTouchingHead(QGraphicsItem *item);
    bool isTouchingPlatform(QGraphicsItem *item);
    void stand();
    void jump();
    void standShoot();
    void crouch();
    void walk();
    void fall();
    bool isFalling();

private:
    enum State {
         Standing = 0,
         StandShoot,
         Crouching,
         Walking,
         Jumping,
         Falling
    };

    int m_direction;
    int mCurrentFrame;
    int m_StandingDirection;
    int m_CrouchingDirection;
    State mState;
    QPixmap mPixmap;
    QPixmap mWalkPixmap;
    QPixmap mStandingPixmap;
    QPixmap mJumpPixmap;
    QPixmap standShootPixmap;
    QPixmap crouchPixmap;

    };
#endif // PLAYER_H
