#ifndef ALIEN_H
#define ALIEN_H

#include "spaceship.h"


class Alien : public SpaceShip
{
    Q_OBJECT

public:
    Alien(QPixmap sprite, QGraphicsItem *parent);
    ~Alien();
    QTimer * bTimer;

signals:
    void sigAlienOutOfRange();

public slots:
    void move();

};

#endif // ALIEN_H
