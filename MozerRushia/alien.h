#ifndef ALIEN_H
#define ALIEN_H

#include "spaceship.h"

#include <QTimer>

class Alien : public SpaceShip
{
    Q_OBJECT

public:
    Alien(QPixmap sprite, QGraphicsItem *parent, QTimer * timer, int speed, QTimer * alienShootTimer);
    ~Alien();

signals:
    void sigAlienOutOfRange(Alien*);
    void sigAlienShoot(Alien*);
public slots:
    void onMove();
    void onShoot();

};

#endif // ALIEN_H
