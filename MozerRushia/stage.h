#ifndef STAGE_H
#define STAGE_H

#include "alien.h"

class Stage:public QObject
{
    Q_OBJECT

public:
    Stage(QTimer * timer, QPixmap alienSprite = QPixmap(":/Asteroid"));
    void setNumberOfAliens(int n);
    int getNumberOfAliens() { return numberOfAliens; }
    void setAlienSpritePixmap(QPixmap alienSprite);

signals:
    void sigDecreaseHealthOutOfRange();

public slots:
    void onSpawn(QGraphicsScene *scene);
    void onAlienOutOfRange();

private:
    QTimer * moveTimer;
    int level = 1;
    int numberOfAliens = 1;
    QPixmap alienSprite;
};

#endif // STAGE_H
