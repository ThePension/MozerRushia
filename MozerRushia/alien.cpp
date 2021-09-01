#include "alien.h"
#include "player.h"
#include <QTimer>

Alien::Alien(QPixmap sprite, QGraphicsItem *parent, QTimer * timer) : SpaceShip(sprite, parent, timer)
{
    speed = 2;
    connect(timer, &QTimer::timeout, this, &Alien::move);
}

Alien::~Alien()
{

}

void Alien::move()
{
    setPos(x(), y() + speed);

    if(pos().y() > scene()->height())
    {
        emit sigAlienOutOfRange();
        scene()->removeItem(this);
        delete this;
    }
}
