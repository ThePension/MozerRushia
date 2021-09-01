#ifndef PLAYER_H
#define PLAYER_H

#include "spaceship.h"

class Player : public SpaceShip
{
    Q_OBJECT
public:
    Player(QPixmap sprite, QGraphicsItem * parent, QTimer * timer);
    ~Player();

signals:
    void sigAlienRocketCollision();

public slots:
    void onMove();
};

#endif // PLAYER_H
