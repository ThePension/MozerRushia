#include "alien.h"
#include "player.h"

Alien::Alien(QPixmap sprite, QGraphicsItem *parent) : SpaceShip(sprite, parent)
{
    speed = 1;
}

void Alien::move()
{
    setPos(x(), y() + speed);
}
