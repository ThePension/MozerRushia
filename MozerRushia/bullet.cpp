#include "bullet.h"
#include "alien.h"
#include "stage.h"

Bullet::Bullet(QPixmap sprite, int speed, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
    this->speed = speed;
    setPixmap(sprite.scaled(bulletSize, Qt::KeepAspectRatio));
    QTimer * bTimer = new QTimer();
    connect (bTimer, &QTimer::timeout, this, &Bullet::onMove);
    bTimer->start(1000/FPS);
}

void Bullet::onMove()
{
    QList<QGraphicsItem*> firstCollidingItem = collidingItems();

   for(auto const pItem : firstCollidingItem)
   {
       Alien* pAlien = dynamic_cast<Alien*>(pItem);
       if(pAlien != nullptr)
       {
           scene()->removeItem(pAlien);
           scene()->removeItem(this);

           emit sigAlienCollision();
           delete pAlien;
           delete this;
       }
   }

    setPos(x(), y() - this->speed);

    if (pos().y()<0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
