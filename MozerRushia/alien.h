#ifndef ALIEN_H
#define ALIEN_H

#include "spaceship.h"


class Alien : public SpaceShip
{
    Q_OBJECT
public:
    Alien(QPixmap sprite, QGraphicsItem *parent);

    void move();

signals:
    void sigAlienRocketCollision();
};

#endif // ALIEN_H
