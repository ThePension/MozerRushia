#include "weapon.h"
#include "bullet.h"

Weapon::Weapon()
{

}

void Weapon::shoot(int posPlayerSpaceShip)
{
    QPixmap bSprite(":/PlayerRocket.png");
    Bullet* bullet = new Bullet(bSprite, nullptr);

    bullet->setPos(posPlayerSpaceShip,75);
    scene()->addItem(bullet);
}
