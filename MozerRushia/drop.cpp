#include "drop.h"
#include "player.h"
#include <stdlib.h>

Drop::Drop(int speed, QGraphicsItem *parent, QTimer *moveTimer) : QGraphicsPixmapItem(parent)
{
    this->speed = speed;
    QPixmap sprite;
    type = (rand() % 3 + 1);
    switch (type) {
        case 1:
            sprite = (QPixmap)":/Drop_Weapon_Up.png";
            break;
        case 2:
            sprite = (QPixmap)":/Drop_Weapon_Down.png";
            break;
        case 3:
            sprite = (QPixmap)":/Drop_Life.png";
            break;
    }

    setPixmap(sprite.scaled(dropSize, Qt::KeepAspectRatio));
    connect(moveTimer, &QTimer::timeout, this, &Drop::onMove);
}

Drop::~Drop()
{

}

void Drop::onMove()
{
    setPos(x(), y() + this->speed);
    if(this->pos().y() > scene()->height())
    {
        emit sigDropOutOfRange(this);
    }
}
