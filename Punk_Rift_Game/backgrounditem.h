/*
 * Author: Jonathan Baird
 * Date: 1/29/2017
 * Purpose: MVC SEC Video Game Punk Rift
*/

#ifndef BACKGROUNDITEM_H
#define BACKGROUNDITEM_H

#include <QGraphicsPixmapItem>

class BackgroundItem : public QGraphicsPixmapItem
{
public:
    explicit BackgroundItem(const QPixmap &pixmap, QGraphicsItem *parent = 0);

public:
    virtual QPainterPath shape() const;

    };
#endif // BACKGROUNDITEM_H
