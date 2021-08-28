#include "game.h"
#include "settings.h"
#include <QPixmap>
#include <QTimer>

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
    player = new Player(QPixmap(":/PlayerRocket.png"), nullptr);
    player->setPos(width() / 2, height() - spaceShipSize.height());
    scene()->addItem(player);

    QTimer * moveTimer = new QTimer();
    moveTimer->start(1000/FPS);
    // Connection for player movements
    connect(moveTimer, &QTimer::timeout, player, &Player::move);
}

void Game::test()
{

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
    if(e->key() == Qt::Key_Left || e->key() == Qt::Key_Right)
        player->direction = Direction::any;
}
