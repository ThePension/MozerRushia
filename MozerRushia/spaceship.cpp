#include "spaceship.h"

SpaceShip::SpaceShip(QPixmap sprite, QGraphicsItem * parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(sprite.scaled(spaceShipSize, Qt::KeepAspectRatio));
}
