#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsPixmapItem>

#include"settings.h"


#ifndef WEAPON_H
#define WEAPON_H


class Weapon : public QGraphicsPixmapItem
{
public:
    Weapon(QGraphicsItem * parent);
    void shoot(int posPlayerSpaceShipX, int posPlayerSpaceShipY);

private:
    double cadence = 1;
    int damage = 1;
    int speed = 3;
    //enum weaponType;
};

#endif // WEAPON_H
