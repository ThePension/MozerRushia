#include "bullet.h"

Bullet::Bullet(QPixmap sprite, int speed, double offsetX, QGraphicsItem* parent, QTimer * moveTimer) : QGraphicsPixmapItem(parent)
{
    this->speed = speed;
    setPixmap(sprite.scaled(bulletSize, Qt::KeepAspectRatio));
    connect(moveTimer, &QTimer::timeout, this, &Bullet::onMove);
    offset = offsetX;
}

Bullet::~Bullet()
{

}

void Bullet::onMove()
{
    QList<QGraphicsItem*> firstCollidingItem = collidingItems();
    for(auto const pItem : firstCollidingItem)
    {
        Alien* pAlien = dynamic_cast<Alien*>(pItem);
        if(pAlien != nullptr)
        {
            emit sigAlienBulletCollision(pAlien, this);
        }
    }

    setPos(x() + offset, y() - this->speed);
    if(this->pos().y() < 0)
    {
        emit sigBulletOutOfRange(this);
    }

}

