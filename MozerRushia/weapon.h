#ifndef WEAPON_H
#define WEAPON_H

#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsPixmapItem>

#include "settings.h"

class Weapon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Weapon(QGraphicsItem * parent, QTimer * timer);
    void shoot(int posPlayerSpaceShipX, int posPlayerSpaceShipY, int weaponNumber);
    int weaponNumber = 1;

signals:
    void sigScore();

public slots:
    void onAlienCollision();

private:
    double cadence = 1;
    int damage = 1;
    int speed = 5;
    QTimer * moveTimer;
    //enum weaponType;
};

#endif // WEAPON_H
