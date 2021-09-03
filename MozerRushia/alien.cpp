#include "alien.h"
#include <QTimer>

Alien::Alien(QPixmap sprite, QGraphicsItem *parent, QTimer * timer, int speedAlien) : SpaceShip(sprite, parent)
{
    this->speed = speedAlien;
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
