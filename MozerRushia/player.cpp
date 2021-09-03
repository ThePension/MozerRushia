#include "player.h"
#include <QTimer>
#include <QGraphicsScene>

Player::Player(QPixmap sprite, QGraphicsItem *parent, QTimer * timer) : SpaceShip(sprite, parent)
{
    currentWeapon = new Weapon(this, timer);
}

Player::~Player()
{
    delete currentWeapon;
    currentWeapon = nullptr;
}


void Player::onMove()
{
    switch (direction) {
        case Direction::any:
            // Sprite droit
            setPixmap(QPixmap(":/PlayerRocket.png").scaled(spaceShipSize, Qt::KeepAspectRatio));
            break;
        case Direction::left:
            if(x() > 0) setPos(x() - speed, y());
            setPixmap(QPixmap(":/PlayerRocket_Left.png").scaled(spaceShipSize, Qt::KeepAspectRatio));
            break;
        case Direction::right:
            if(x() < scene()->width() - spaceShipSize.width()) setPos(x() + speed, y());
            setPixmap(QPixmap(":/PlayerRocket_Right.png").scaled(spaceShipSize, Qt::KeepAspectRatio));
    }

    QList<QGraphicsItem*> firstCollidingItem = collidingItems();

    for(auto const pItem : firstCollidingItem)
    {
        Alien* pAlien = dynamic_cast<Alien*>(pItem);
        if(pAlien != nullptr)
        {
            emit sigAlienPlayerCollision(pAlien);
        }
    }
    for(auto const pItem : firstCollidingItem)
    {
        Drop* pDrop = dynamic_cast<Drop*>(pItem);
        if(pDrop != nullptr)
        {
            emit sigDropPlayerCollision(pDrop);
        }
    }

}

