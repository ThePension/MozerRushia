#include "bullet.h"

Bullet::Bullet(QPixmap sprite, double offsetX, double offsetY, QGraphicsItem* parent, QTimer * moveTimer) : QGraphicsPixmapItem(parent)
{
    this->offsetY = offsetY;
    this->offsetX = offsetX;
    setPixmap(sprite.scaled(bulletSize, Qt::KeepAspectRatio));
    connect(moveTimer, &QTimer::timeout, this, &Bullet::onMove);
}

Bullet::~Bullet()
{

}

void Bullet::onMove()
{
    setPos(x() + offsetX, y() + offsetY);
    if(this->pos().y() < -alienSize.height() - 100 || this->pos().y() > scene()->height())
    {
        emit sigBulletOutOfRange(this);
        return;
    }
    QList<QGraphicsItem*> firstCollidingItem = collidingItems();
    if(this->offsetY < 0){
        for(auto const pItem : firstCollidingItem)
        {
            Alien* pAlien = dynamic_cast<Alien*>(pItem);
            if(pAlien != nullptr)
            {
                emit sigAlienBulletCollision(pAlien, this);
                return;
            }
        }
    }
    if(this->offsetY > 0){
        for(auto const pItem : firstCollidingItem)
        {
            Player* pPlayer = dynamic_cast<Player*>(pItem);
            if(pPlayer != nullptr)
            {
                emit sigPlayerBulletCollision(this);
                return;
            }
        }
    }
}

