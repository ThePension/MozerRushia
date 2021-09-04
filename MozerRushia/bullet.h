#ifndef BULLET_H
#define BULLET_H

#include<QGraphicsPixmapItem>
#include<QGraphicsScene>
#include<QTimer>

#include "settings.h"
#include "alien.h"
#include "player.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Bullet(QPixmap sprite, double offsetX, double offsetY, QGraphicsItem* parent, QTimer * moveTimer);
    ~Bullet();
    double offsetY = 0;
    double offsetX = 0;

signals:
    void sigBulletOutOfRange(Bullet *);
    void sigAlienBulletCollision(Alien*, Bullet*);
    void sigPlayerBulletCollision(Bullet*);

private slots :
    void onMove();
};

#endif // BULLET_H
