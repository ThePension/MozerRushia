#include "game.h"
#include "settings.h"
#include "stage.h"
#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <QPushButton>
#include <QApplication>
#include <QHBoxLayout>
#include <windows.h>
#include <mmsystem.h>
#include <QDir>

Game::Game(QWidget *parent, QSize * screenSize) : QGraphicsView(parent)
{
    QGraphicsScene * scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Creating Quit button
    quitButton = new MenuButton(this);
    quitButton->setText("Quitter le jeu");
    quitButton->setGeometry(QRect(scene->width() / 2 - 200, scene->height() / 2 + 75, 400, 100));
    scene->addWidget(quitButton);
    quitButton->close();
    connect(quitButton, &MenuButton::clicked, this, &QApplication::quit);
}

void Game::displayMainMenu(){
        // Display the quit button
        quitButton->show();

        // Creating play button
        playButton = new MenuButton(this);
        playButton->setText("Jouer");
        playButton->setGeometry(QRect(scene()->width() / 2 - 200, scene()->height() / 2 - 75, 400, 100));
        scene()->addWidget(playButton);
        connect(playButton, &MenuButton::clicked, this, &Game::run);
        playButton->show();
        playButton->setDefault(true);

        // Menu background image
        scene()->setBackgroundBrush(QPixmap(":/Fond_Menu.png").scaled(scene()->width(),scene()->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

        // Music theme
        // Code tiré de https://www.debugcn.com/en/article/14341438.html - copie les fichiers resources Qt dans le \temp du système
        QString path = QDir::temp().absoluteFilePath("mainTheme.wav");
        QFile::copy(":/mainTheme.wav", path);
        PlaySound((wchar_t*)path.utf16(), NULL, SND_FILENAME | SND_ASYNC);
}
void Game::run()
{
    scene()->clear();
    // Background image
    qScrollingBg = new QGraphicsPixmapItem();
    QPixmap bgPixmap = QPixmap(":/Fond_Game.jpg").scaledToWidth(scene()->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - scene()->height()));
    scene()->addItem(qScrollingBg);

    // Menu's buttons
    playButton->close();
    quitButton->close();

    // Player creation
    player = new Player(QPixmap(":/PlayerRocket.png"), nullptr);
    player->setPos(width() / 2, height() - spaceShipSize.height());
    scene()->addItem(player);

    // Main timer
    moveTimer = new QTimer();
    moveTimer->start(1000/FPS);

    // Connection for player movements
    connect(moveTimer, &QTimer::timeout, player, &Player::move);

    // Stages creation
    Stage *stage = new Stage();
    QTimer *spawnTimer = new QTimer();
    spawnTimer->start(3000);
    connect(spawnTimer, &QTimer::timeout, [=](){ stage->spawn(scene()); });

    // Rotate view
    /*
    QTransform transform;
    transform.rotate(90);
    setTransform(transform);
    */

    // HUD Display
    HUDMan=new HUD(nullptr);
    scene()->addItem(HUDMan);
    HUDMan->show();
    connect(player->currentWeapon, &Weapon::sigScore, this, &Game::onIncreaseScore);
    connect(player, &Player::sigAlienRocketCollision, this, &Game::onDecreaseHealth);
    connect(stage, &Stage::sigDecreaseHealthOutOfRange, this, &Game::onDecreaseHealth);

    // Scrolling background connection
    connect(moveTimer, &QTimer::timeout, this, &Game::onBackgroundScrolling);
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

void Game::CheckPoints()
{
    if ((HUDMan->GetScore()<0) || (HUDMan->GetHealth() <=0))
    {
        HUDMan->Reset();
        onGameOver();
    }
}

void Game::onIncreaseScore()
{
    HUDMan->IncreaseScore();
    CheckPoints();
}

void Game::onDecreaseHealth()
{
    HUDMan->DecreaseHealth();
    CheckPoints();
}

void Game::onGameOver()
{
    close();
}

void Game::onBackgroundScrolling()
{
    qScrollingBg->setPos(qScrollingBg->pos().x(), qScrollingBg->pos().y() + 1);
}
