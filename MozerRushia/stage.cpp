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

void Stage::onSpawn(QGraphicsScene *scene)
{
    Alien *a = new Alien(QPixmap(":/Asteroid"), nullptr, moveTimer);
    int posX = rand() % int(scene->width() - 150);
    scene->addItem(a);
    a->setPos(posX, -alienSize.height());

    connect(a,&Alien::sigAlienOutOfRange,this,&Stage::onAlienOutOfRange);
}

void Stage::onAlienOutOfRange()
{
    emit sigDecreaseHealthOutOfRange();
}

