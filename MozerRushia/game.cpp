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

    // Creating game scene
    gameScene = new QGraphicsScene(this);
    gameScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Creation menu scene
    mainMenuScene = new MainMenu(this, screenSize);
    mainMenuScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Creation narration Scene
    historyScene = new QGraphicsScene(this);
    historyScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    historyScene->setBackgroundBrush(QPixmap(":/Narration_Test.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    // Timers creations
    spawnTimer = new QTimer();
    moveTimer = new QTimer();


}

void Game::displayMainMenu(){
    // Connect menu's buttons
    connect(mainMenuScene->playArcadeButton, &MenuButton::clicked, this, &Game::runArcade);
    connect(mainMenuScene->playHistoryButton, &MenuButton::clicked, this, &Game::run);
    connect(mainMenuScene->quitButton, &MenuButton::clicked, this, &QApplication::quit);

    // Set the scene with mainMenu scene
    setScene(mainMenuScene);

    // Music theme
    // Code tiré de https://www.debugcn.com/en/article/14341438.html - copie les fichiers resources Qt dans le \temp du système
    /*QString path = QDir::temp().absoluteFilePath("mainTheme.wav");
    QFile::copy(":/mainTheme.wav", path);
    PlaySound((wchar_t*)path.utf16(), NULL, SND_FILENAME | SND_ASYNC);*/
}
void Game::run()
{
    // Creation of background item
    qScrollingBg = new QGraphicsPixmapItem();
    gameScene->addItem(qScrollingBg);

    //next level button
    nxtLvl = new MenuButton(nullptr);
    nxtLvl->setText("Continuer");
    nxtLvl->setGeometry(QRect(width()-210, height()-110, 200, 100));
    historyScene->addWidget(nxtLvl);
    connect(nxtLvl,&MenuButton::clicked,this,&Game::onChangeLevel);

    // Changing for the scene game
    setScene(gameScene);


    // Creation resume button for pause menu
    resumeButton = new MenuButton(this);
    resumeButton->setText("Continuer");
    resumeButton->setGeometry(QRect(width() / 2 - 200, height() / 2 - 75, 400, 100));
    gameScene->addWidget(resumeButton);
    connect(resumeButton, &MenuButton::clicked, this, &Game::resumeTheGame);

    // Creation quit button for pause menu
    quitButton = new MenuButton(this);
    quitButton->setText("Quitter le jeu");
    quitButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 75, 400, 100));
    gameScene->addWidget(quitButton);
    connect(quitButton, &MenuButton::clicked, this, &QApplication::quit);

    // Background image
    qScrollingBg = new QGraphicsPixmapItem();
    QPixmap bgPixmap = QPixmap(":/Fond_Game.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
    gameScene->addItem(qScrollingBg);

    if(currentLvl == 1) onChangeLevel();

    // Main timer
    moveTimer->start(1000/FPS);

    // Player creation
    player = new Player(QPixmap(":/PlayerRocket.png"), nullptr, moveTimer);
    player->setPos(width() / 2, height() - spaceShipSize.height());
    gameScene->addItem(player);

    // Connection for player movements
    connect(moveTimer, &QTimer::timeout, player, &Player::onMove, Qt::UniqueConnection);

    // Stages creation
    stage = new Stage(moveTimer);
    spawnTimer->start(3000);
    connect(spawnTimer, &QTimer::timeout, this, &Game::onSpawn, Qt::UniqueConnection);

    // Rotate view
    /*
    QTransform transform;
    transform.rotate(90);
    setTransform(transform);
    */

    // HUD Display //peut etre lié au niveau et pas générique finalement
    HUDMan=new HUD(nullptr);
    scene()->addItem(HUDMan);
    HUDMan->show();
    connect(player->currentWeapon, &Weapon::sigScore, this, &Game::onIncreaseScore);
    connect(player, &Player::sigAlienRocketCollision, this, &Game::onDecreaseHealth);
    connect(stage, &Stage::sigDecreaseHealthOutOfRange, this, &Game::onDecreaseHealth);

    // Scrolling background connection
    connect(moveTimer, &QTimer::timeout, this, &Game::onBackgroundScrolling, Qt::UniqueConnection);
}

void Game::runLvl1()
{
    QPixmap bgPixmap = QPixmap(":/Fond_Game.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
    currentLvl+=1;
}

void Game::runLvl2()
{
    run();
    QPixmap bgPixmap = QPixmap(":/Fond_Game.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
}

void Game::runLvl3()
{
    /*run();
    QPixmap bgPixmap = QPixmap(":/Fond_Game.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));*/
}

void Game::runArcade()
{
    // Changing for the scene game
    setScene(gameScene);

    // Creation resume button for pause menu
    resumeButton = new MenuButton(this);
    resumeButton->setText("Continuer");
    resumeButton->setGeometry(QRect(width() / 2 - 200, height() / 2 - 75, 400, 100));
    gameScene->addWidget(resumeButton);
    connect(resumeButton, &MenuButton::clicked, this, &Game::resumeTheGame);

    // Creation quit button for pause menu
    quitButton = new MenuButton(this);
    quitButton->setText("Quitter le jeu");
    quitButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 75, 400, 100));
    gameScene->addWidget(quitButton);
    connect(quitButton, &MenuButton::clicked, this, &QApplication::quit);

    // Background 1 image
    qScrollingBg = new QGraphicsPixmapItem();
    QPixmap bgPixmap = QPixmap(":/Seamless_Background.png").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
    gameScene->addItem(qScrollingBg);

    // Background 2 image
    qScrollingBg2 = new QGraphicsPixmapItem();
    qScrollingBg2->setPixmap(bgPixmap);
    qScrollingBg2->setPos(0, -bgPixmap.size().height());
    gameScene->addItem(qScrollingBg2);


    // Main timer
    moveTimer->start(1000/FPS);

    // Player creation
    player = new Player(QPixmap(":/PlayerRocket.png"), nullptr, moveTimer);
    player->setPos(width() / 2, height() - spaceShipSize.height());
    gameScene->addItem(player);

    // Connection for player movements
    connect(moveTimer, &QTimer::timeout, player, &Player::onMove, Qt::QueuedConnection);

    // Stages creation
    Stage *stage = new Stage(moveTimer);
    spawnTimer->start(3000);
    connect(spawnTimer, &QTimer::timeout, [=](){ stage->onSpawn(gameScene); });

    // HUD Display
    HUDMan=new HUD(nullptr);
    scene()->addItem(HUDMan);
    HUDMan->show();
    connect(player->currentWeapon, &Weapon::sigScore, this, &Game::onIncreaseScore);
    connect(player, &Player::sigAlienRocketCollision, this, &Game::onDecreaseHealth);
    connect(stage, &Stage::sigDecreaseHealthOutOfRange, this, &Game::onDecreaseHealth);

    // Scrolling background connection
    connect(moveTimer, &QTimer::timeout, this, &Game::onArcadeModeBackgroundScrolling);
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
                    pauseTheGame();
                }
                else{
                    resumeTheGame();
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

void Game::pauseTheGame()
{
    moveTimer->stop(); // Pause the game
    spawnTimer->stop();
    resumeButton->show();
    quitButton->show();
}

void Game::resumeTheGame()
{
    resumeButton->close();
    quitButton->close();
    moveTimer->start(1000/FPS); // Restart
    spawnTimer->start(3000);
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

void Game::onChangeLevel()
{
    switch (currentLvl)
    {
    case 0:
        runArcade();
        break;
    case 1:
        runLvl1();
        break;
    case 2:
        runLvl2();
        break;
    case 3:
        runLvl3();
        break;
    default:
        runLvl1();
        break;
    }
}

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

void Game::onArcadeModeBackgroundScrolling()
{
    qScrollingBg->setPos(qScrollingBg->pos().x(), qScrollingBg->pos().y() + 1);
    qScrollingBg2->setPos(qScrollingBg2->pos().x(), qScrollingBg2->pos().y() + 1);
    if(qScrollingBg->pos().y() >= screenSize->height())
    {
        qScrollingBg->setPos(0, -qScrollingBg->pixmap().size().height());
    }
    else if(qScrollingBg2->pos().y() >= screenSize->height()){
        qScrollingBg2->setPos(0, -qScrollingBg2->pixmap().size().height());
    }
}

void Game::onSpawn()
{
    stage->onSpawn(gameScene);
}
