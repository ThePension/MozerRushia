#include "spaceship.h"
#include "bullet.h"

SpaceShip::SpaceShip(QPixmap sprite, QGraphicsItem * parent, QTimer * timer) : QGraphicsPixmapItem(parent)
{
    setPixmap(sprite.scaled(spaceShipSize, Qt::KeepAspectRatio));
}
