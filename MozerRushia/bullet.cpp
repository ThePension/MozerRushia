#include "bullet.h"

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
    /* QList<QGraphicsItem*> firstCollidingItem = collidingItems();

    for(auto const pItem : firstCollidingItem)
    {
        CAlien* pAlien = dynamic_cast<CAlien*>(pItem);
        if(pAlien != nullptr)
        {
            if(pAlien->GetColor() == GetColor())
            {
                scene()->removeItem(pAlien);
                scene()->removeItem(this);

                emit sigIncreaseScore();

                delete pAlien;
                delete this;
            }
            else
            {
                emit sigDecreaseScore();
                scene()->removeItem(this);
                delete this;
            }
            return;
        }
    }*/

    setPos(x(), y() - this->speed);

    if (pos().y()<0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
