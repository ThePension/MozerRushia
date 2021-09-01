#include "stage.h"
#include "game.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <algorithm>
#include "player.h"

Stage::Stage(QTimer * timer)
{
    moveTimer = timer;
}

void Stage::setNumberOfAliens(int n)
{
    numberOfAliens = n;
}

void Stage::onSpawn(QGraphicsScene *scene)
{
    for(int i = 0; i < numberOfAliens; i++){
        Alien *a = new Alien(QPixmap(":/Asteroid"), nullptr, moveTimer);
        int posX = rand() % int(scene->width() - 150);
        scene->addItem(a);
        a->setPos(posX, -alienSize.height());

        connect(a,&Alien::sigAlienOutOfRange,this,&Stage::onAlienOutOfRange);
    }
}

void Stage::onAlienOutOfRange()
{
    emit sigDecreaseHealthOutOfRange();
}

