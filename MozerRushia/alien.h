#ifndef ALIEN_H
#define ALIEN_H

#include "spaceship.h"


class Alien : public SpaceShip
{
    Q_OBJECT

public:
    Alien(QPixmap sprite, QGraphicsItem *parent, QTimer * timer, int speed);
    ~Alien();

signals:
    void sigAlienOutOfRange(Alien*);
public slots:
    void onMove();

};

#endif // ALIEN_H
