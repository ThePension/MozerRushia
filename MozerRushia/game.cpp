#include "game.h"
#include "settings.h"
#include "stage.h"
#include "drop.h"
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


        QApplication::setOverrideCursor(Qt::ArrowCursor);

    // Remove white border of view
    this->setStyleSheet("border-width: 0px; border-style: solid");

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
    connect(gameOverMenu->quitButton, &MenuButton::clicked, this, &QApplication::quit, Qt::UniqueConnection);
    connect(gameOverMenu->backToMenuButton, &MenuButton::clicked, this, &Game::displayMainMenu, Qt::UniqueConnection);
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
    // Hide cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // Reset scene rect
    gameScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    gameScene->clear();
    this->viewport()->update();
    // Timers creations
    spawnTimer = new QTimer();
    moveTimer = new QTimer();

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
            connect(nxtLvl,&MenuButton::clicked,this,&Game::onChangeLevel, Qt::UniqueConnection);
            break;
        }
        case 2:
        {
            nxtLvl->setText("Continuer");
            connect(nxtLvl,&MenuButton::clicked,this,&Game::onChangeLevel, Qt::UniqueConnection);
            break;
        }
        case 3:
        {
            rotateView(180);
            nxtLvl->setText("Finir");
            connect(nxtLvl,&MenuButton::clicked,this,&QApplication::quit, Qt::UniqueConnection); //will close the game if the narrative isn't finish
            break;
        }
        default:
        {
            connect(nxtLvl,&MenuButton::clicked,this,&Game::onChangeLevel, Qt::UniqueConnection);
            break;
        }

    }

    // Changing for the scene game
    setScene(gameScene);

    // Creation resume button for pause menu
    resumeButton = new MenuButton(this);
    resumeButton->setText("Continuer");
    resumeButton->setGeometry(QRect(width() / 2 - 200, height() / 2 - 60, 400, 100));
    gameScene->addWidget(resumeButton);
    connect(resumeButton, &MenuButton::clicked, this, &Game::resumeTheGame, Qt::UniqueConnection);

    // Creation quit button for pause menu
    quitButton = new MenuButton(this);
    quitButton->setText("Quitter le jeu");
    quitButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 200, 400, 100));
    gameScene->addWidget(quitButton);
    connect(quitButton, &MenuButton::clicked, this, &QApplication::quit, Qt::UniqueConnection);

    // Creation back to menu button for pause menu
    backToMenuButton = new MenuButton(this);
    backToMenuButton->setText("Menu principal");
    backToMenuButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 60, 400, 100));
    gameScene->addWidget(backToMenuButton);
    connect(backToMenuButton, &MenuButton::clicked, this, &Game::onBackToMainMenu, Qt::UniqueConnection);

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
    connect(player, &Player::sigAlienPlayerCollision, this, &Game::onAlienPlayerCollision);
    connect(player, &Player::sigDropPlayerCollision, this, &Game::onDropPlayerCollision, Qt::UniqueConnection);
    connect(this, &Game::sigPlayerShoot, this, &Game::onPlayerShoot, Qt::UniqueConnection);
    // Connection for player movements
    connect(moveTimer, &QTimer::timeout, player, &Player::onMove, Qt::UniqueConnection);


    // Stages creation
    stage = new Stage(moveTimer);
    spawnTimer->start(spawnTimeInterval);
    connect(spawnTimer, &QTimer::timeout, this, &Game::onSpawn, Qt::UniqueConnection);

    // HUD Display //peut etre lié au niveau et pas générique finalement
    HUDMan=new HUD(nullptr);
    scene()->addItem(HUDMan); //Pourquoi scene et pas gameScene ?
    HUDMan->show();

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
    QPixmap bgPixmap = QPixmap(":/BackGround_Lvl2.jpg").scaledToWidth(gameScene->width());
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
    QPixmap bgPixmap = QPixmap(":/BackGround_Lvl3.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
    currentLvl+=1;
}

void Game::runArcade()
{
    // Hide cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // Reset scene rect
    gameScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    gameScene->clear();
    this->viewport()->update();

    // Timers creations
    spawnTimer = new QTimer();
    moveTimer = new QTimer();

    // Replay button connection
    connect(gameOverMenu->replayButton, &MenuButton::clicked, this, &Game::runArcade, Qt::UniqueConnection);

    // Changing for the scene game
    setScene(gameScene);

    // Creation resume button for pause menu
    resumeButton = new MenuButton(this);
    resumeButton->setText("Continuer");
    resumeButton->setGeometry(QRect(width() / 2 - 200, height() / 2 - 60, 400, 100));
    gameScene->addWidget(resumeButton);
    connect(resumeButton, &MenuButton::clicked, this, &Game::resumeTheGame, Qt::UniqueConnection);

    // Creation quit button for pause menu
    quitButton = new MenuButton(this);
    quitButton->setText("Quitter le jeu");
    quitButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 200, 400, 100));
    gameScene->addWidget(quitButton);
    connect(quitButton, &MenuButton::clicked, this, &QApplication::quit, Qt::UniqueConnection);

    // Creation back to menu button for pause menu
    backToMenuButton = new MenuButton(this);
    backToMenuButton->setText("Menu principal");
    backToMenuButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 60, 400, 100));
    gameScene->addWidget(backToMenuButton);
    connect(backToMenuButton, &MenuButton::clicked, this, &Game::onBackToMainMenu, Qt::UniqueConnection);

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
    connect(player, &Player::sigAlienPlayerCollision, this, &Game::onAlienPlayerCollision);
    connect(player, &Player::sigDropPlayerCollision, this, &Game::onDropPlayerCollision);
    connect(this, &Game::sigPlayerShoot, this, &Game::onPlayerShoot, Qt::UniqueConnection);
    // Connection for player movements
    connect(moveTimer, &QTimer::timeout, player, &Player::onMove, Qt::UniqueConnection);

    // Stages creation
    stage = new Stage(moveTimer, QPixmap(":/Asteroid.png"));
    spawnTimer->start(spawnTimeInterval);
    connect(spawnTimer, &QTimer::timeout, this, &Game::onSpawnArcade, Qt::UniqueConnection);

    // Difficulty management
    difficultyTimer = new QTimer();
    difficultyTimer->start(10000); // Increase the number of aliens by 1 every 10 seconds
    connect(difficultyTimer, &QTimer::timeout,[this]()  mutable {
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
    //connect(player->currentWeapon, &Weapon::sigScore, this, &Game::onIncreaseScore);
    //connect(player, &Player::sigAlienPlayerCollision, this, &Game::onDecreaseHealth);
    //connect(stage, &Stage::sigDecreaseHealthOutOfRange, this, &Game::onDecreaseHealth);
    //connect(player, &Player::sigIncreaseHealth, this, &Game::onIncreaseHealth);
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
                if(moveTimer != nullptr){
                    if(moveTimer->isActive()){
                        if(!e->isAutoRepeat()){ // Check if the key is held : if it is, call the shoot function once
                            emit sigPlayerShoot();
                        }
                    }
                }
                break;
            case Qt::Key_Escape:
                if(moveTimer != nullptr){
                    if(moveTimer != nullptr && moveTimer->isActive()) {
                        pauseTheGame();
                    }
                    else{
                        resumeTheGame();
                    }
                }
                break;
            case Qt::Key_Q:
                if(moveTimer != nullptr && moveTimer->isActive()){
                    if(player->currentWeapon->weaponNumber >= 3){
                        player->currentWeapon->weaponNumber -= 2;
                    }
                }
                break;
            case Qt::Key_E:
                if(moveTimer != nullptr && moveTimer->isActive()){
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
    backToMenuButton->show();
    quitButton->show();
    // Show cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void Game::resumeTheGame()
{
    resumeButton->close();
    quitButton->close();
    backToMenuButton->close();
    moveTimer->start(1000/FPS); // Restart
    spawnTimer->start(spawnTimeInterval);
    // Hide cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);
}

void Game::onIncreaseScore()
{
    hitCount+=1;
    HUDMan->setScore(hitCount*50, hitLive);
    //CheckPoints();
}

void Game::increaseHealth()
{
    hitLive+=1;
    HUDMan->setScore(hitCount*50, hitLive);
    //CheckPoints();
}

void Game::decreaseHealth()
{
    hitLive-=1;
    HUDMan->setScore(hitCount*50, hitLive);
    //CheckPoints();
    if (hitLive <=0)
    {
        hitLive=3;
        onGameOver();
        HUDMan->reset();
        //onGameOver();
    }
}

void Game::onAlienPlayerCollision(Alien* pAlien)
{
    decreaseHealth();
    if(pAlien != nullptr)
    {
        gameScene->removeItem(pAlien);
        delete pAlien;
    }

}

void Game::onDropPlayerCollision(Drop* pDrop)
{
    gameScene->removeItem(pDrop);
    switch(pDrop->type)
    {
        case 1:
            if(player->currentWeapon->weaponNumber <= 3)
                player->currentWeapon->weaponNumber += 2;
            break;
        case 2:
            if(player->currentWeapon->weaponNumber >= 3)
                player->currentWeapon->weaponNumber -= 2;
            break;
        case 3:
            increaseHealth();
            break;
    }
    delete pDrop;
}

void Game::onAlienBulletCollision(Alien* pAlien, Bullet* pBullet)
{

    if(rand() % 5 == 0) // 20% chances to spawn a drop
    {
        qDebug() << "Drop";
        Drop *pDrop = new Drop(pAlien->speed, nullptr, moveTimer);
        pDrop->setPos(pAlien->pos());
        gameScene->addItem(pDrop);
    }
        onIncreaseScore();
    gameScene->removeItem(pAlien);
    gameScene->removeItem(pBullet);
    delete pAlien;
    delete pBullet;

}

void Game::onAlienOutOfRange(Alien* pAlien)
{
    //decreaseHealth();
    gameScene->removeItem(pAlien);
    delete pAlien;
    decreaseHealth();
}

void Game::onBulletOutOfRange(Bullet* pBullet)
{
    gameScene->removeItem(pBullet);
    delete pBullet;
}

void Game::onDropOutOfRange(Drop* pDrop)
{
    gameScene->removeItem(pDrop);
    delete pDrop;
}

void Game::onPlayerShoot()
{
    QPixmap bSprite(":/SovietBullet.png");
    Bullet *pBullet;
    int weaponNumber = player->currentWeapon->weaponNumber;
    double angle = -0.25*weaponNumber;
    if(weaponNumber == 1)
    {angle = 0;}
    for(int i = 0; i < weaponNumber; i++)
    {
        pBullet = new Bullet(bSprite, 5, angle, nullptr, moveTimer); //A voir pour charger le speed depuis les settings
        pBullet->setPos(player->pos().x() + bulletSize.width() / 2, player->pos().y() - bulletSize.height() / 2);
        gameScene->addItem(pBullet);
        connect(pBullet, &Bullet::sigBulletOutOfRange, this, &Game::onBulletOutOfRange, Qt::UniqueConnection);
        connect(pBullet, &Bullet::sigAlienBulletCollision, this, &Game::onAlienBulletCollision, Qt::UniqueConnection);
        angle += 0.5;
    }
}

void Game::onGameOver()
{
    // Change scene for game over
    setScene(gameOverMenu);


    this->resetTransform();

    // Delete timers
    delete difficultyTimer;
    delete moveTimer;
    delete spawnTimer;

    // Delete attributes that are in gameScene
    delete player;
    delete stage;
    delete qScrollingBg;
    delete qScrollingBg2;
    delete backToMenuButton;
    delete quitButton;
    delete resumeButton;

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

    // Delete next level button
    /*delete nxtLvl;
    nxtLvl = nullptr;*/
    currentLvl = 1;



    // Show cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}
//ajouter un autre gameover (pour histoire afin de recommencer au début du jeu)
void Game::onChangeLevel()
{
    switch (currentLvl)
    {
    case 1:
        spawnTimeInterval=1500;
        runLvl1();
        historyScene->setBackgroundBrush(QPixmap(":/Narration_Test.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    case 2:
        spawnTimeInterval=500;
        runLvl2();
        historyScene->setBackgroundBrush(QPixmap(":/Narration_Test.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    case 3:
        spawnTimeInterval=750;
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

        // Show cursor
        QApplication::setOverrideCursor(Qt::ArrowCursor);
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
            spawn(QPixmap(":/Asteroid.png"));
            break;
        case 3:
            spawn(QPixmap(":/AlienShip_Lvl2.png"));
            break;
        case 4:
            spawn(QPixmap(":/AmericanShuttle_Lvl.png"));
            break;
    }
}

void Game::onSpawnArcade()
{
    int randSprite = rand()%(3);
    switch (randSprite) {
        case 0:
            spawn(QPixmap(":/Asteroid.png"));
            //stage->setAlienSpritePixmap(QPixmap(":/Asteroid.png"));
            break;
        case 1:
            spawn(QPixmap(":/AlienShip.png"));
            //stage->setAlienSpritePixmap(QPixmap(":/AlienShip.png"));
            break;
        case 2:
            spawn(QPixmap(":/AmericanShuttle_Lvl.png"));
            //stage->setAlienSpritePixmap(QPixmap(":/AlienRocket.png"));
            break;
    }
    //stage->onSpawn(gameScene);
}

void Game::spawn(QPixmap sprite)
{
    Alien *pAlien = new Alien(sprite, nullptr, moveTimer);
    int posX = rand() % int(scene()->width() - alienSize.width());
    scene()->addItem(pAlien);
    pAlien->setPos(posX, -alienSize.height());
    connect(pAlien, &Alien::sigAlienOutOfRange, this, &Game::onAlienOutOfRange);
}

void Game::onBackToMainMenu()
{
    // Delete pause button (because gameScene->clear doesn't do it if they're attributes of Game class)
    delete backToMenuButton;
    backToMenuButton = nullptr;
    delete resumeButton;
    resumeButton = nullptr;
    delete quitButton;
    quitButton = nullptr;

    // Delete timers
    delete moveTimer;
    moveTimer = nullptr;
    delete spawnTimer;
    spawnTimer = nullptr;
    if(difficultyTimer != nullptr) {
        delete difficultyTimer;
        difficultyTimer = nullptr;
    }

    // Delete attributes that are in gameScene
    delete player;
    player = nullptr;
    delete stage;
    stage = nullptr;
    delete qScrollingBg;
    qScrollingBg = nullptr;
    delete qScrollingBg2;
    qScrollingBg2 = nullptr;
    delete backToMenuButton;
    backToMenuButton = nullptr;
    delete quitButton;
    quitButton = nullptr;
    delete resumeButton;
    resumeButton = nullptr;

    // Reset the view if it was rotated
    this->resetTransform();
    gameScene->setSceneRect(0, 0, screenSize->height(), screenSize->width());

    // Delete next level button
    delete nxtLvl;
    nxtLvl = nullptr;
    currentLvl = 1;

    // Clear all scenes
    gameScene->clear();
    // historyScene->clear();

    displayMainMenu();
}
