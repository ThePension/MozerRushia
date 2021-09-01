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

public slots:
    void spawn(QGraphicsScene *scene);
    void sloAlienOutOfRange();

private:
    QTimer * moveTimer;
    int level = 1;
};

#endif // STAGE_H
