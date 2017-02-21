/*
 * Author: Jonathan Baird
 * Date: 1/29/2017
 * Purpose: MVC SEC Video Game Punk Rift
*/


#include "backgrounditem.h"

BackgroundItem::BackgroundItem(const QPixmap &pixmap, QGraphicsItem * parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
}

QPainterPath BackgroundItem::shape() const
{
    return QPainterPath();
}
