#include<QGraphicsPixmapItem>
#include<QGraphicsScene>
#include<QTimer>

#include "settings.h"

#ifndef BULLET_H
#define BULLET_H


class Bullet : public QGraphicsPixmapItem, public QObject
{
public:
    Bullet(QPixmap sprite, int speed, QGraphicsItem* parent);
    int speed;
private slots :
    void onMove();
};

#endif // BULLET_H
