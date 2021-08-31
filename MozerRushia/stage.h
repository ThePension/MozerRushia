#ifndef STAGE_H
#define STAGE_H

#include "alien.h"

class Stage
{
public:
    Stage();
private:

    int level = 1;

public slots:
    void spawn(QGraphicsScene *scene);
    void increaseScore();
};

#endif // STAGE_H
