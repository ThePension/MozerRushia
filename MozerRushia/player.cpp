#include "player.h"
#include <QTimer>
#include <QGraphicsScene>
Player::Player(QPixmap * sprite, QGraphicsItem *parent, QObject * objParent) : SpaceShip(sprite, parent, objParent)
{
    QTimer * moveTimer = new QTimer();
    moveTimer->start(1000/60);
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
            setPixmap(sprite.scaled(QSize(50, 50), Qt::KeepAspectRatio));
            break;
        case Direction::left:
            if(x() > 0) setPos(x() - speed, y());
            setPixmap(spriteLeft.scaled(QSize(50, 50), Qt::KeepAspectRatio));
            break;
        case Direction::right:
            if(x() < scene()->width() - 50) setPos(x() + speed, y());
            setPixmap(spriteRight.scaled(QSize(50, 50), Qt::KeepAspectRatio));
    }
}
