#ifndef ALIEN_H
#define ALIEN_H

#include "spaceship.h"


class Alien : public SpaceShip
{
public:
    Alien(QPixmap sprite, QGraphicsItem *parent);

    void move();
};

#endif // ALIEN_H
