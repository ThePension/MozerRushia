#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>

#include "settings.h"

class SpaceShip : public QObject, public QGraphicsPixmapItem
{
public:
    SpaceShip(QPixmap sprite, QGraphicsItem * parent);
    int HP = 3;
    double speed = 5;
    Direction direction = any;
};

#endif // SPACESHIP_H
