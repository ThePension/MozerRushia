#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>

#include "Direction.h"

class SpaceShip : public QGraphicsPixmapItem, public QObject
{
public:
    SpaceShip(QPixmap * sprite, QGraphicsItem * parent, QObject * objParent);
    int HP = 3;
    double speed = 10;
    Direction direction = any;
};

#endif // SPACESHIP_H
