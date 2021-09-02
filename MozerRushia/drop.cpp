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
    QList<QGraphicsItem*> firstCollidingItem = collidingItems();

    for(auto const pItem : firstCollidingItem)
    {
        Player *pPlayer = dynamic_cast<Player*>(pItem);
        if(pPlayer != nullptr)
        {
            switch (type) {
                case 1:
                    if(pPlayer->currentWeapon->weaponNumber <=3)
                        pPlayer->currentWeapon->weaponNumber += 2;
                    break;
                case 2:
                    if(pPlayer->currentWeapon->weaponNumber >= 3)
                        pPlayer->currentWeapon->weaponNumber -= 2;
                    break;
                case 3:
                    break;
            }
            //pPlayer->currentWeapon->weaponNumber += 2;
            scene()->removeItem(this);
            return;
        }

    }

    setPos(x(), y() + this->speed);
}
