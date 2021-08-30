#include "player.h"
#include <QTimer>
#include <QGraphicsScene>
Player::Player(QPixmap sprite, QGraphicsItem *parent) : SpaceShip(sprite, parent)
{
    currentWeapon = new Weapon(this);
}


void Player::move()
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
}
