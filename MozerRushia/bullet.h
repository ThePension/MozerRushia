#ifndef BULLET_H
#define BULLET_H

#include<QGraphicsPixmapItem>
#include<QGraphicsScene>
#include<QTimer>

#include "settings.h"
#include "alien.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Bullet(QPixmap sprite, int speed, double offset, QGraphicsItem* parent, QTimer * moveTimer);
    ~Bullet();
    int speed;
    double offset = 0;

signals:
    void sigBulletOutOfRange(Bullet *);
    void sigAlienBulletCollision(Alien*, Bullet*);
private:
    QTimer *timer;
private slots :
    void onMove();
};

#endif // BULLET_H
