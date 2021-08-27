#include "player.h"
#include <QTimer>
#include <QGraphicsScene>
Player::Player(QPixmap * sprite, QGraphicsItem *parent) : SpaceShip(sprite, parent)
{
    QTimer * moveTimer = new QTimer(this);
    moveTimer->start(1000/FPS);
    connect(moveTimer, &QTimer::timeout, this, &Player::move);
}


void Player::move()
{
    QPixmap sprite(":/PlayerRocket.png");
    QPixmap spriteLeft(":/PlayerRocket_Left.png");
    QPixmap spriteRight(":/PlayerRocket_Right.png");
    switch (direction) {
        case Direction::any:
            // Sprite droit
            setPixmap(sprite.scaled(spaceShipSize, Qt::KeepAspectRatio));
            break;
        case Direction::left:
            if(x() > 0) setPos(x() - speed, y());
            setPixmap(spriteLeft.scaled(spaceShipSize, Qt::KeepAspectRatio));
            break;
        case Direction::right:
            if(x() < scene()->width() - spaceShipSize.width()) setPos(x() + speed, y());
            setPixmap(spriteRight.scaled(spaceShipSize, Qt::KeepAspectRatio));
    }
}
