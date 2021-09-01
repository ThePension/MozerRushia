#include "weapon.h"
#include "bullet.h"

Weapon::Weapon(QGraphicsItem * parent, QTimer * timer) : QGraphicsPixmapItem(parent)
{
    moveTimer = timer;
}

void Weapon::shoot(int posPlayerSpaceShipX, int posPlayerSpaceShipY, int weaponNumber)
{
    QPixmap bSprite(":/SovietBullet.png");
    Bullet * bullet;
    double angle= -0.25*weaponNumber;
    if(weaponNumber == 1)
    {angle = 0;}
    for(int i = 0; i < weaponNumber; i++)
    {

        bullet = new Bullet(bSprite, speed, angle, nullptr, moveTimer);
        bullet->setPos(posPlayerSpaceShipX + spaceShipSize.width() / 2 - bulletSize.width() / 2, posPlayerSpaceShipY - bulletSize.height() / 2);
        scene()->addItem(bullet);
        connect(bullet,&Bullet::sigAlienCollision,this,&Weapon::sloAlienCollision);
        angle += 0.25*2;
    }
}
void Weapon::sloAlienCollision()
{
    emit sigScore();
}
