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
#include <QDebug>

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

    // Creation game over scene
    gameOverMenu = new GameOverMenu(this, screenSize);
    gameOverMenu->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    connect(gameOverMenu->quitButton, &MenuButton::clicked, this, &QApplication::quit);
    connect(gameOverMenu->backToMenuButton, &MenuButton::clicked, this, &Game::displayMainMenu);

    // Timers creations
    spawnTimer = new QTimer();
    moveTimer = new QTimer();
}

void Game::displayMainMenu(){
    // Connect menu's buttons
    connect(mainMenuScene->playArcadeButton, &MenuButton::clicked, this, &Game::runArcade, Qt::UniqueConnection);
    connect(mainMenuScene->playHistoryButton, &MenuButton::clicked, this, &Game::run, Qt::UniqueConnection);
    connect(mainMenuScene->quitButton, &MenuButton::clicked, this, &QApplication::quit, Qt::UniqueConnection);

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
    // Replay button connection
    connect(gameOverMenu->replayButton, &MenuButton::clicked, this, &Game::run, Qt::UniqueConnection);

    // Creation of background item
    qScrollingBg = new QGraphicsPixmapItem();
    gameScene->addItem(qScrollingBg);

    //next level button
    nxtLvl = new MenuButton(nullptr);
    nxtLvl->setGeometry(QRect(width()-210, height()-110, 200, 100));
    historyScene->addWidget(nxtLvl);
    switch(currentLvl)
    {
        case 1:
        {
            nxtLvl->setText("Continuer");
            connect(nxtLvl,&MenuButton::clicked,this,&Game::onChangeLevel);
            break;
        }
        case 2:
        {
            nxtLvl->setText("Continuer");
            //rotateView(270);
            //gameScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
            //nxtLvl->setGeometry(QRect(width()/2, height()/2, 200, 100));
            connect(nxtLvl,&MenuButton::clicked,this,&Game::onChangeLevel);
            break;
        }
        case 3:
        {
            rotateView(180);
            nxtLvl->setText("Finir");
            connect(nxtLvl,&MenuButton::clicked,this,&QApplication::quit); //will close the game if the narrative isn't finish
            break;
        }
        default:
        {
            connect(nxtLvl,&MenuButton::clicked,this,&Game::onChangeLevel);
            break;
        }

    }

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

    // HUD Display //peut etre lié au niveau et pas générique finalement
    HUDMan=new HUD(nullptr);
    scene()->addItem(HUDMan); //Pourquoi scene et pas gameScene ?
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
    HUDMan->setScore(hitCount*50,hitLive);
    rotateView(90);
    HUDMan->setRotation(-90);
    HUDMan->rotation();
    gameScene->setSceneRect(0, 0, screenSize->height(), screenSize->width());
    HUDMan->setPos(50,screenSize->width()-50);
    HUDMan->pos();
    player->setPos(height() / 2, width() - spaceShipSize.height());
    QPixmap bgPixmap = QPixmap(":/Fond_Game.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
    currentLvl+=1;
}

void Game::runLvl3()
{
    run();
    HUDMan->setScore(hitCount*50, hitLive);
    rotateView(180);
    HUDMan->setRotation(-180);
    HUDMan->rotation();
    gameScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    HUDMan->setPos(screenSize->width()-50,screenSize->height()-50);
    HUDMan->pos();
    QPixmap bgPixmap = QPixmap(":/Fond_Game.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
    currentLvl+=1;
}

void Game::runArcade()
{
    // Replay button connection
    connect(gameOverMenu->replayButton, &MenuButton::clicked, this, &Game::runArcade, Qt::UniqueConnection);

    // Changing for the scene game
    setScene(gameScene);

    // Creation resume button for pause menu
    resumeButton = new MenuButton(this);
    resumeButton->setText("Continuer");
    resumeButton->setGeometry(QRect(width() / 2 - 200, height() / 2 - 75, 400, 100));
    gameScene->addWidget(resumeButton);
    connect(resumeButton, &MenuButton::clicked, this, &Game::resumeTheGame, Qt::UniqueConnection);

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
    connect(moveTimer, &QTimer::timeout, player, &Player::onMove, Qt::UniqueConnection);

    // Stages creation
    stage = new Stage(moveTimer, QPixmap(":/Asteroid.png"));
    int spawnTimeInterval = 1000;
    spawnTimer->start(spawnTimeInterval);
    connect(spawnTimer, &QTimer::timeout, this, &Game::onSpawnArcade, Qt::UniqueConnection);

    // Difficulty management
    QTimer * difficulty = new QTimer();
    difficulty->start(10000); // Increase the number of aliens by 1 every 10 seconds

    connect(difficulty, &QTimer::timeout, [spawnTimeInterval, this]() mutable {
        // stage->setNumberOfAliens(stage->getNumberOfAliens() + 1);
        if(moveTimer->isActive()){
            if(spawnTimeInterval > 500) spawnTimeInterval -= 100;
            else spawnTimeInterval = 500;
            spawnTimer->stop();
            spawnTimer->start(spawnTimeInterval);
        }
    });

    // HUD Display
    HUDMan=new HUD(nullptr);
    gameScene->addItem(HUDMan);
    HUDMan->show();
    connect(player->currentWeapon, &Weapon::sigScore, this, &Game::onIncreaseScore);
    connect(player, &Player::sigAlienRocketCollision, this, &Game::onDecreaseHealth);
    connect(stage, &Stage::sigDecreaseHealthOutOfRange, this, &Game::onDecreaseHealth);

    // Scrolling background connection
    connect(moveTimer, &QTimer::timeout, this, &Game::onArcadeModeBackgroundScrolling, Qt::UniqueConnection);
}

void Game::rotateView(int rotationDegree)
{
    QTransform transform;
    transform.rotate(rotationDegree);
    setTransform(transform);

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
                if(moveTimer->isActive()){
                    if(!e->isAutoRepeat()){ // Check if the key is held : if it is, call the shoot function once
                        player->currentWeapon->shoot(player->pos().x(), player->pos().y(), player->currentWeapon->weaponNumber);
                    }
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
    if (hitLive <=0)
    {
        hitLive=3;
        HUDMan->reset();
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
    hitCount+=1;
    HUDMan->setScore(hitCount*50, hitLive);
    CheckPoints();
}

void Game::onIncreaseHealth()
{
    hitLive+=1;
    HUDMan->setScore(hitCount*50, hitLive);
    CheckPoints();
}

void Game::onDecreaseHealth()
{
    hitLive-=1;
    HUDMan->setScore(hitCount*50, hitLive);
    CheckPoints();
}

void Game::onGameOver()
{
    // Change scene for game over
    setScene(gameOverMenu);

    // Stop timers
    moveTimer->stop();
    spawnTimer->stop();

    // Display the score
    QTextDocument * oldDocument = gameOverMenu->scoreText->document();
    delete oldDocument;
    oldDocument = nullptr;
    QTextDocument * document = new QTextDocument();
    QTextCharFormat charFormat;
    charFormat.setFont(QFont("", 50, QFont::Bold));
    QPen outlinePen = QPen(Qt::black, 2, Qt::SolidLine);
    charFormat.setTextOutline(outlinePen);
    QTextCursor cursor = QTextCursor(document);
    cursor.clearSelection();
    cursor.insertText("Score : " + QString::number(hitCount*50), charFormat);
    gameOverMenu->scoreText->setDocument(document);

    // Reset the score
    hitCount = 0;

    // Clear the game scene
    gameScene->clear();
}
//ajouter un autre gameover (pour histoire afin de recommencer au début du jeu)
void Game::onChangeLevel()
{
    switch (currentLvl)
    {
    case 1:
        runLvl1();
        historyScene->setBackgroundBrush(QPixmap(":/Narration_Test.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    case 2:
        runLvl2();
        historyScene->setBackgroundBrush(QPixmap(":/Narration_Test.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    case 3:
        runLvl3();
        historyScene->setBackgroundBrush(QPixmap(":/Narration_Test_3.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    default:
        runLvl1();
        historyScene->setBackgroundBrush(QPixmap(":/Narration_Test.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    }
}

void Game::onBackgroundScrolling()
{
    qScrollingBg->setPos(qScrollingBg->pos().x(), qScrollingBg->pos().y() + 1);

    if(qScrollingBg->pos().y()>=0)
    {
        this->resetTransform();
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
    switch (currentLvl)
    {
        case 2:
            stage->setAlienSpritePixmap(QPixmap(":/Asteroid.png"));
            break;
        case 3:
            stage->setAlienSpritePixmap(QPixmap(":/AlienShip.png"));
            break;
        case 4:
            stage->setAlienSpritePixmap(QPixmap(":/AlienRocket.png"));
            break;
    }
    stage->onSpawn(gameScene);
}

void Game::onSpawnArcade()
{
    int randSprite = rand()%(3);
    switch (randSprite) {
        case 0:
            stage->setAlienSpritePixmap(QPixmap(":/Asteroid.png"));
            break;
        case 1:
            stage->setAlienSpritePixmap(QPixmap(":/AlienShip.png"));
            break;
        case 2:
            stage->setAlienSpritePixmap(QPixmap(":/AlienRocket.png"));
            break;
    }
    stage->onSpawn(gameScene);
}
