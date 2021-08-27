#ifndef PLAYER_H
#define PLAYER_H

#include "spaceship.h"

class Player : public SpaceShip
{
public:
    Player(QPixmap * sprite, QGraphicsItem * parent, QObject * objParent);
    int score = 0;
    void move();
};

#endif // PLAYER_H
