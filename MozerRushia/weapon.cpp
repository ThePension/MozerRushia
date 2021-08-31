#include "weapon.h"
#include "bullet.h"

Weapon::Weapon(QGraphicsItem * parent) : QGraphicsPixmapItem(parent)
{

}

void Weapon::shoot(int posPlayerSpaceShipX, int posPlayerSpaceShipY)
{
    QPixmap bSprite(":/SovietBullet.png");
    Bullet * bullet = new Bullet(bSprite, speed, nullptr);

    bullet->setPos(posPlayerSpaceShipX + spaceShipSize.width() / 2 - bulletSize.width() / 2, posPlayerSpaceShipY - bulletSize.height() / 2);
    scene()->addItem(bullet);

    connect(bullet,&Bullet::sigAlienCollision,this,&Weapon::sloAlienCollision);
}
void Weapon::sloAlienCollision()
{
    emit sigScore();
}
