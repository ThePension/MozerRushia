#ifndef ALIEN_H
#define ALIEN_H

#include "spaceship.h"


class Alien : public SpaceShip
{
    Q_OBJECT

public:
    Alien(QPixmap sprite, QGraphicsItem *parent, QTimer * timer);
    ~Alien();

signals:
    void sigAlienOutOfRange();

public slots:
    void onMove();

};

#endif // ALIEN_H
