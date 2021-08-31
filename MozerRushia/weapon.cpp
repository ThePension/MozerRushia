#include "weapon.h"
#include "bullet.h"

Weapon::Weapon(QGraphicsItem * parent) : QGraphicsPixmapItem(parent)
{

}

void Weapon::shoot(int posPlayerSpaceShipX, int posPlayerSpaceShipY)
{
    QPixmap bSprite(":/SovietBullet.png");
    Bullet * bullet = new Bullet(bSprite, speed, nullptr);

    bullet->setPos(posPlayerSpaceShipX + 50, posPlayerSpaceShipY);
    scene()->addItem(bullet);

    connect(bullet,&Bullet::sigAlienCollision,this,&Weapon::sloAlienCollision);
}
void Weapon::sloAlienCollision()
{
    emit sigScore();
}
