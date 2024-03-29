#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>

#include "settings.h"
#include "weapon.h"
#include "drop.h"

 class SpaceShip : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    SpaceShip(QPixmap sprite, QGraphicsItem * parent);
    int HP = 3;
    double speed = 10;
    Weapon * currentWeapon;
    Direction direction = any;
};

#endif // SPACESHIP_H
