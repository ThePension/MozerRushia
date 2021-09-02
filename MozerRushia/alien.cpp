#include "alien.h"
#include "player.h"
#include <QTimer>

Alien::Alien(QPixmap sprite, QGraphicsItem *parent, QTimer * timer) : SpaceShip(sprite, parent, timer)
{
    speed = 2;
    connect(timer, &QTimer::timeout, this, &Alien::onMove);
}

Alien::~Alien()
{

}

void Alien::onMove()
{
   /* QList<QGraphicsItem*> firstCollidingItem = collidingItems();
    for(auto const pItem : firstCollidingItem)
    {
        Bullet* pBullet = dynamic_cast<Bullet*>(pItem);
        if(pBullet != nullptr)
        {
            emit sigAlienBulletCollision(this, pBullet);
        }
    }*/

    setPos(x(), y() + speed);

    if(pos().y() > scene()->height())
    {
        emit sigAlienOutOfRange(this);
    }
}
