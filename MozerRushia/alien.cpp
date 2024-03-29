#include "alien.h"

Alien::Alien(QPixmap sprite, QGraphicsItem *parent, QTimer * timer, int speedAlien, QTimer * alienShootTimer) : SpaceShip(sprite, parent)
{
    this->speed = speedAlien;
    connect(timer, &QTimer::timeout, this, &Alien::onMove);
    QPixmap americanSprite(":/AmericanShuttle_Lvl.png");
    if(sprite.toImage() == americanSprite.toImage()){ // Only shoot if it's american
        connect(alienShootTimer, &QTimer::timeout, this, &Alien::onShoot);
    }
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

void Alien::onShoot()
{
    emit sigAlienShoot(this);
}
