#ifndef WEAPON_H
#define WEAPON_H

#include<QGraphicsView>
#include<QGraphicsPixmapItem>

#include "settings.h"

class Weapon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Weapon(QGraphicsItem * parent, QTimer * timer);

    int weaponNumber = 1;
private:
    QTimer * moveTimer;
};

#endif // WEAPON_H
