#include "stage.h"
#include "game.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <algorithm>

Stage::Stage()
{

}

void Stage::spawn(QGraphicsScene *scene)
{

    Alien *a = new Alien(QPixmap(":/AlienRocket"), nullptr);
    int posX = rand() % int(scene->width() - 150);
    scene->addItem(a);
    a->setPos(posX, 0);
    aliens.push_back(a);

}

void Stage::moveAliens()
{
    for(unsigned i = 0; i < aliens.size(); i++)
    {
        aliens[i]->move();
    }
}
void Stage::removeAlien(Alien *a)
{
    aliens.erase(std::remove(aliens.begin(), aliens.end(), a), aliens.end());

}
