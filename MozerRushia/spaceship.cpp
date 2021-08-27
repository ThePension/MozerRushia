#include "spaceship.h"
#include "bullet.h"

SpaceShip::SpaceShip(QPixmap * sprite, QGraphicsItem * parent, QObject * objParent) : QGraphicsPixmapItem(parent), QObject(objParent)
{
    setPixmap(sprite->scaled(QSize(50, 50), Qt::KeepAspectRatio));
}
