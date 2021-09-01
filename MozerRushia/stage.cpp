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

void Stage::spawn(QGraphicsScene *scene)
{

    Alien *a = new Alien(QPixmap(":/AlienRocket"), nullptr, moveTimer);
    int posX = rand() % int(scene->width() - 150);
    scene->addItem(a);
    a->setPos(posX, -alienSize.height());

    connect(a,&Alien::sigAlienOutOfRange,this,&Stage::sloAlienOutOfRange);
}

void Stage::sloAlienOutOfRange()
{
    emit sigDecreaseHealthOutOfRange();
}

