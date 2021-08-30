#include "game.h"
#include "settings.h"
#include "stage.h"
#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <QPushButton>
#include <QApplication>
#include <QHBoxLayout>

Game::Game(QWidget *parent, QSize * screenSize) : QGraphicsView(parent)
{
    QGraphicsScene * scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Quit button
    quitButton = new QPushButton(this);
    quitButton->setText("Quitter le jeu");
    quitButton->setGeometry(QRect(scene->width() / 2 - 100, scene->height() / 2 - quitButton->size().height() - 50, 200, 100));
    scene->addWidget(quitButton);
    quitButton->close();
    connect(quitButton, &QPushButton::clicked, this, &QApplication::quit);
}

void Game::displayMainMenu(){
        // create the title text
        QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Mozer Rushia"));
        QFont titleFont("comic sans", 50);
        titleText->setFont(titleFont);
        titleText->setDefaultTextColor(Qt::red);
        int txPos = this->width()/2 - titleText->boundingRect().width()/2;
        int tyPos = 150;
        titleText->setPos(txPos,tyPos);
        scene()->addItem(titleText);

        // Display the quit button
        quitButton->show();

        // Creating play button
        playButton = new QPushButton(this);
        playButton->setText("Jouer");
        playButton->setGeometry(QRect(scene()->width() / 2 - 100, scene()->height() / 2 - quitButton->size().height() + 200, 200, 100));
        scene()->addWidget(playButton);
        connect(playButton, &QPushButton::clicked, this, &Game::run);
        playButton->show();
        playButton->setDefault(true);

        // Menu background image
        scene()->setBackgroundBrush(QPixmap(":/Fond_Menu.png").scaled(scene()->width(),scene()->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void Game::run()
{
    scene()->clear();
    scene()->setBackgroundBrush(QPixmap(":/Fond_Provisoire.png").scaled(scene()->width(),scene()->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    playButton->close();
    quitButton->close();
    player = new Player(QPixmap(":/PlayerRocket.png"), nullptr);
    player->setPos(width() / 2, height() - spaceShipSize.height());
    scene()->addItem(player);

    moveTimer = new QTimer();
    moveTimer->start(1000/FPS);
    // Connection for player movements
    connect(moveTimer, &QTimer::timeout, player, &Player::move);

    Stage *stage = new Stage();
    QTimer *spawnTimer = new QTimer();
    spawnTimer->start(3000);
    connect(spawnTimer, &QTimer::timeout, [=](){stage->spawn(scene());});
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
                if(!e->isAutoRepeat()){ // Check if the key is held : if it is, call the shoot function once
                    player->currentWeapon->shoot(player->pos().x(), player->pos().y());
                }
                break;
            case Qt::Key_Escape:
                if(moveTimer->isActive()){
                    moveTimer->stop(); // Pause the game
                    // Display "Quit" button
                    quitButton->show();
                }
                else {
                    moveTimer->start(1000/FPS); // Restart
                    // Remove "Quit" button
                    quitButton->close();
                }
                break;
        }
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
    // Direction
    if(e->key() == Qt::Key_Left || e->key() == Qt::Key_Right)
        player->direction = Direction::any;
}
