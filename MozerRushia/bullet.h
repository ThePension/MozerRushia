#include<QGraphicsPixmapItem>
#include<QGraphicsScene>
#include<QTimer>

#include "settings.h"
#include "alien.h"

#ifndef BULLET_H
#define BULLET_H


class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QPixmap sprite, int speed, QGraphicsItem* parent);
    int speed;
public:
signals:
    void sigAlienCollision();
private slots :
    void onMove();
};

#endif // BULLET_H
