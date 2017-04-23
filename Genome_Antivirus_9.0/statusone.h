#ifndef STATUSONE_H
#define STATUSONE_H

#include <QGraphicsPixmapItem>

class StatusOne : public QGraphicsPixmapItem
{
public:
    explicit StatusOne(const QPixmap &pixmap, QGraphicsItem *parent = 0);

public:
    virtual QPainterPath shape() const;
};
#endif // STATUSONE_H
