#ifndef PLAYER_H
#define PLAYER_H

#include <QTimer>
#include <QGraphicsScene>

#include "spaceship.h"
#include "alien.h"
#include "drop.h"

class Player : public SpaceShip
{
    Q_OBJECT
public:
    Player(QPixmap sprite, QGraphicsItem * parent, QTimer * timer);
    ~Player();

signals:
    void sigAlienPlayerCollision(Alien*);
    void sigDropPlayerCollision(Drop*);

public slots:
    void onMove();
};

#endif // PLAYER_H
