#include "statusone.h"

StatusOne::StatusOne(const QPixmap &pixmap, QGraphicsItem * parent) : QGraphicsPixmapItem(pixmap, parent)
{

}

QPainterPath StatusOne::shape() const
{
    return QPainterPath();
}
