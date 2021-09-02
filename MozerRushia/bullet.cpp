#include "bullet.h"
#include "alien.h"
#include "stage.h"
#include "drop.h"

Bullet::Bullet(QPixmap sprite, int speed, double offsetX, QGraphicsItem* parent, QTimer * moveTimer) : QGraphicsPixmapItem(parent)
{
    this->speed = speed;
    setPixmap(sprite.scaled(bulletSize, Qt::KeepAspectRatio));
    connect(moveTimer, &QTimer::timeout, this, &Bullet::onMove);
    offset = offsetX;
    timer = moveTimer;
}

Bullet::~Bullet()
{

}

void Bullet::onMove()
{
    QList<QGraphicsItem*> firstCollidingItem = collidingItems();
    Drop *d = nullptr;
    QPointF posAlien;
    for(auto const pItem : firstCollidingItem)
    {
        Alien* pAlien = dynamic_cast<Alien*>(pItem);
        if(pAlien != nullptr)
        {
            posAlien = pAlien->pos();
            scene()->removeItem(pAlien);
            emit sigAlienCollision();
            delete pAlien;

            this->setPos(0,0);
            if((rand() % 5) == 0){
               d = new Drop(speed, nullptr, timer);
               d->setPos(posAlien.x(), posAlien.y());

               scene()->addItem(d);

            }
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    setPos(x() + offset, y() - this->speed);

    if (pos().y()<0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
