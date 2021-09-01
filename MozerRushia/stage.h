#ifndef STAGE_H
#define STAGE_H

#include "alien.h"

class Stage:public QObject
{
    Q_OBJECT

public:
    Stage(QTimer * timer);

signals:
    void sigDecreaseHealthOutOfRange();

private:
    QTimer * moveTimer;
    int level = 1;

public slots:
    void spawn(QGraphicsScene *scene);
    void sloAlienOutOfRange();
};

#endif // STAGE_H
