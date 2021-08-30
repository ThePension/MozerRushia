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
    void removeAlien(Alien *a);

public slots:
    void spawn(QGraphicsScene *scene);
    void moveAliens();
    void increaseScore();
};

#endif // STAGE_H
