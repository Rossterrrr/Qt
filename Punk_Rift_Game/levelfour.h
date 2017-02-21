/*
 * Author: Jonathan Baird
 * Date: 1/29/2017
 * Purpose: MVC SEC Video Game Punk Rift
*/

#ifndef LEVELFOUR_H
#define LEVELFOUR_H
#include <QGraphicsScene>
#include <QTimer>
#include <QAbstractAnimation>
#include <QDebug>

class QGraphicsPixmapItem;
class QPropertyAnimation;

class BackgroundItem;
class Player;

class Platform;
class QScrollBar;


class LevelFour : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)
public:
    explicit LevelFour(QScrollBar* s, QObject *parent = 0);
    void timerEvent(QTimerEvent *);
    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);
    void sendSignalFour();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void movePlayer();
    void jumpPlayer();
    void fallPlayer();
    void checkTimer();

    bool handleCollisionWithPlatform();

    QGraphicsItem* collidingPlatforms();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);


signals:
    void jumpFactorChanged(qreal);
    //void playSound(QString);
     void endLevelFour();

private:
    void initPlayField();

    int m_velocity;
    int m_skippedMoving;
    qreal m_groundLevel;
    qreal m_minX;
    qreal m_maxX;
    QTimer m_timer;
    QTimer mFallTimer;
    QPropertyAnimation *m_jumpAnimation;
    qreal m_jumpFactor;
    int m_jumpHeight;
    int m_fieldWidth;


    Player *m_player;
    Platform *m_Platform;

    BackgroundItem *m_Background;
    BackgroundItem *m_Scene;
    BackgroundItem *m_ground;

    QGraphicsItem *m_platform;

    QGraphicsItem *platform;
    QScrollBar *scroll;

    Platform *p1;
    Platform *p2;
};
#endif // LEVELFOUR_H
