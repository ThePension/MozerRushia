#ifndef STAGE_H
#define STAGE_H

#include "alien.h"

class Stage
{
public:
    Stage();
    std::vector<Alien*> aliens;
private:
    //std::vector<*Alien> aliens;
    int level = 1;

public slots:
    void spawn(QGraphicsScene *scene);
    void moveAliens();
    void increaseScore();
    void removeAlien(Alien *a);
};

#endif // STAGE_H
