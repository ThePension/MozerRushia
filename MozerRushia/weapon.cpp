#include "weapon.h"

Weapon::Weapon(QGraphicsItem * parent, QTimer * timer) : QGraphicsPixmapItem(parent)
{
    moveTimer = timer;
}
