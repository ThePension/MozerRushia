#include "alien.h"
#include <QTimer>

Alien::Alien(QPixmap sprite, QGraphicsItem *parent, QTimer * timer) : SpaceShip(sprite, parent)
{
    speed = 2;
    connect(timer, &QTimer::timeout, this, &Alien::onMove);
}

Alien::~Alien()
{

}

void Alien::onMove()
{
    setPos(x(), y() + speed);

    if(pos().y() > scene()->height())
    {
        emit sigAlienOutOfRange(this);
    }
}
