#ifndef PLAYER_H
#define PLAYER_H

#include "spaceship.h"

class Player : public QObject, public SpaceShip
{
public:
    Player(QPixmap sprite, QGraphicsItem * parent);
    int score = 0;
public slots:
    void move();
};

#endif // PLAYER_H
