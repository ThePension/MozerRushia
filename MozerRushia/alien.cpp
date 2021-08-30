#include "alien.h"
#include "player.h"

Alien::Alien(QPixmap sprite, QGraphicsItem *parent) : SpaceShip(sprite, parent)
{
    speed = 1;
}

void Alien::move()
{
   QList<QGraphicsItem*> firstCollidingItem = collidingItems();

   for(auto const pItem : firstCollidingItem)
   {
       Player* pPlayer = dynamic_cast<Player*>(pItem);
       if(pPlayer != nullptr)
       {
           scene()->removeItem(this);

           emit sigAlienRocketCollision();
       }
   }

    setPos(x(), y() + speed);
}
