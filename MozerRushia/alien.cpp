#include "alien.h"
#include "player.h"
#include <QTimer>

Alien::Alien(QPixmap sprite, QGraphicsItem *parent) : SpaceShip(sprite, parent)
{
    speed = 1;
    bTimer = new QTimer();
    connect(bTimer, &QTimer::timeout, this, &Alien::move);
    bTimer->start(1000/FPS);
}

Alien::~Alien()
{
    delete bTimer;
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
