#ifndef STAGE_H
#define STAGE_H

#include "alien.h"

class Stage:public QObject
{
    Q_OBJECT

public:
    Stage(QTimer * timer);
    void setNumberOfAliens(int n);
    int getNumberOfAliens() { return numberOfAliens; }

signals:
    void sigDecreaseHealthOutOfRange();

public slots:
    void onSpawn(QGraphicsScene *scene);
    void onAlienOutOfRange();

private:
    QTimer * moveTimer;
    int level = 1;
    int numberOfAliens = 1;
};

#endif // STAGE_H
