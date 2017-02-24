/*
 * Author: Jonathan Baird
 * Date: 2/20/2017
 * Purpose: Carl Sagan Video Game
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
