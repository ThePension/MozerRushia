#ifndef PLAYER_H
#define PLAYER_H

#include "spaceship.h"

class Player : public SpaceShip
{
    Q_OBJECT
public:
    Player(QPixmap sprite, QGraphicsItem * parent);
    ~Player();
    //int score = 0;

signals:
    void sigAlienRocketCollision();

public slots:
    void move();
};

#endif // PLAYER_H
