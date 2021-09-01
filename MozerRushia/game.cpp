#include "game.h"
#include "settings.h"
#include "stage.h"
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
    this->screenSize = screenSize;
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Game::displayMainMenu(){
    // Creation menu scene
    mainMenuScene = new MainMenu(this, screenSize);
    mainMenuScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Connect menu's buttons
    connect(mainMenuScene->playButton, &MenuButton::clicked, this, &Game::run);
    connect(mainMenuScene->quitButton, &MenuButton::clicked, this, &QApplication::quit);

    // Set the scene with mainMenu scene
    this->setScene(mainMenuScene);

    // Music theme
    // Code tiré de https://www.debugcn.com/en/article/14341438.html - copie les fichiers resources Qt dans le \temp du système
    QString path = QDir::temp().absoluteFilePath("mainTheme.wav");
    QFile::copy(":/mainTheme.wav", path);
    PlaySound((wchar_t*)path.utf16(), NULL, SND_FILENAME | SND_ASYNC);
}
void Game::run()
{

    // Creation narration Scene
    historyScene = new QGraphicsScene(this);
    historyScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    mainMenuScene->setBackgroundBrush(QPixmap(":/Narration_Test.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    //next level button
    nxtLvl = new MenuButton(nullptr);
    nxtLvl->setText("Continuer");
    nxtLvl->setGeometry(QRect(width()-210, height()-110, 200, 100));
    historyScene->addWidget(nxtLvl);
    connect(nxtLvl,&MenuButton::clicked,this,&QApplication::quit);

    // Creating game scene
    gameScene = new QGraphicsScene(this);
    gameScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Changing for the scene game
    setScene(gameScene);

    // Background image
    qScrollingBg = new QGraphicsPixmapItem();
    QPixmap bgPixmap = QPixmap(":/Fond_Game.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
    gameScene->addItem(qScrollingBg);

    // Main timer
    moveTimer = new QTimer();
    moveTimer->start(1000/FPS);

    // Player creation
    player = new Player(QPixmap(":/PlayerRocket.png"), nullptr, moveTimer);
    player->setPos(width() / 2, height() - spaceShipSize.height());
    gameScene->addItem(player);

    // Connection for player movements
    connect(moveTimer, &QTimer::timeout, player, &Player::move, Qt::QueuedConnection);

    // Stages creation
    Stage *stage = new Stage(moveTimer);
    spawnTimer = new QTimer();
    spawnTimer->start(3000);
    connect(spawnTimer, &QTimer::timeout, [=](){ stage->spawn(gameScene); });

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
                    player->currentWeapon->shoot(player->pos().x(), player->pos().y(), player->currentWeapon->weaponNumber);
                }
                break;
            case Qt::Key_Escape:
                if(moveTimer->isActive()){
                    moveTimer->stop(); // Pause the game
<<<<<<< Updated upstream
                    spawnTimer->stop();
=======
                    // Display "Quit" button
                    mainMenuScene->setBackgroundBrush(QPixmap(":/Fond_Menu.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
>>>>>>> Stashed changes
                    setScene(mainMenuScene);
                }
                else {
                    moveTimer->start(1000/FPS); // Restart
                    spawnTimer->stop();
                    setScene(gameScene);
                }
                break;
            case Qt::Key_Q:
                if(moveTimer->isActive()){
                    if(player->currentWeapon->weaponNumber >= 3){
                        player->currentWeapon->weaponNumber -= 2;
                    }
                }
                break;
            case Qt::Key_E:
                if(moveTimer->isActive()){
                    if(player->currentWeapon->weaponNumber <= 21){
                        player->currentWeapon->weaponNumber += 2;
                    }
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
    mainMenuScene->setBackgroundBrush(QPixmap(":/GameOver.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setScene(mainMenuScene);

    moveTimer->stop();
    spawnTimer->stop();
    gameScene->clear();
}

/*void Game::onChangeLevel()
{
    historyScene->setBackgroundBrush(QPixmap(":/Narration_Test.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setScene(historyScene);

    moveTimer->stop();
    spawnTimer->stop();
    gameScene->clear();
}*/

void Game::onBackgroundScrolling()
{
    qScrollingBg->setPos(qScrollingBg->pos().x(), qScrollingBg->pos().y() + 1);

    if(qScrollingBg->pos().y()>=0) //Valeur critique entre 4266 & 4267 L'idée est la mais nico ça marche pas !!
    {
    historyScene->setBackgroundBrush(QPixmap(":/Narration_Test.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        setScene(historyScene);

        moveTimer->stop();
        spawnTimer->stop();
        gameScene->clear();
    }
}
