#include "alien.h"
#include "player.h"
#include <QTimer>

Alien::Alien(QPixmap sprite, QGraphicsItem *parent) : SpaceShip(sprite, parent)
{
    speed = 1;
    QTimer *bTimer = new QTimer();
    connect(bTimer, &QTimer::timeout, this, &Alien::move);
    bTimer->start(1000/FPS);

}

void Alien::move()
{
    setPos(x(), y() + speed);
}
