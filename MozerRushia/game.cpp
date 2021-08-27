#include "game.h"
#include <QPixmap>

Game::Game(QWidget *parent, QSize * screenSize) : QGraphicsView(parent)
{
    QGraphicsScene * scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Game::run()
{
    scene()->clear();
    player = new Player(new QPixmap(":/PlayerRocket.png"), nullptr, this);
    player->setPos(width() / 2, height() - 50);
    scene()->addItem(player);
}

void Game::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
            case Qt::Key_Left:
                // Direction
                player->direction = Direction::left;
                break;
            case Qt::Key_Right:
                // Direction
                player->direction = Direction::right;
                break;
            case Qt::Key_Space:
                // Shoot
                break;
        }
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
    // Direction
    player->direction = Direction::any;
}
