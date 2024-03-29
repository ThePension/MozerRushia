#include "game.h"

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

    // Creating menu scene
    mainMenuScene = new MainMenu(this, screenSize);
    mainMenuScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Creatibg history Scene
    historyScene = new QGraphicsScene(this);
    historyScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Creating game over scene
    gameOverMenu = new GameOverMenu(this, screenSize);
    gameOverMenu->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    connect(gameOverMenu->quitButton, &MenuButton::clicked, this, &QApplication::quit, Qt::UniqueConnection);
    connect(gameOverMenu->backToMenuButton, &MenuButton::clicked, this, &Game::onBackToMainMenu, Qt::UniqueConnection);

    // Randomize random numbers
    srand((unsigned int)time(NULL));

    // Copy/paste of the musics from the Qt Resources file to \temp
    // Code found and copied from  https://www.debugcn.com/en/article/14341438.html
    QString path = QDir::temp().absoluteFilePath("storyTheme.wav");
    QFile::copy(":/storyTheme.wav", path);
    PlaySound((wchar_t*)path.utf16(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    isArcadeMusicPlaying = 0;
    path = QDir::temp().absoluteFilePath("arcadeTheme.wav");
    QFile::copy(":/arcadeTheme.wav", path);
}

void Game::displayMainMenu(){
    // Connect menu's buttons
    connect(mainMenuScene->playArcadeButton, &MenuButton::clicked, this, &Game::runArcade, Qt::UniqueConnection);
    connect(mainMenuScene->playHistoryButton, &MenuButton::clicked, this, &Game::runHistory, Qt::UniqueConnection);
    connect(mainMenuScene->quitButton, &MenuButton::clicked, this, &QApplication::quit, Qt::UniqueConnection);

    // Set the scene with mainMenu scene
    setScene(mainMenuScene);
}

void Game::runHistory()
{
    // Clear history scene
    historyScene->clear();
    gameScene->clear();

    // Change scene for history scene
    setScene(historyScene);

    // Replay button connection
    connect(gameOverMenu->replayButton, &MenuButton::clicked, this, &Game::runHistory, Qt::UniqueConnection);

    // Create next button
    nxtLvl = new MenuButton(this);
    nxtLvl->setGeometry(QRect(historyScene->width()-210, historyScene->height()-110, 200, 100));
    historyScene->addWidget(nxtLvl);
    nxtLvl->setText("Continuer");
    nxtLvl->show();

    // Naration level 1
    runNarration1();
}

void Game::runNarration1()
{

    isNarrativePlaying = true;
    connect(nxtLvl, &MenuButton::clicked, this, &Game::runNarration1, Qt::UniqueConnection);
    switch (currentNarationStep) {
        case 1:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_A1.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 2:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_A2.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 3:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_A3.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 4:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_A4.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 5:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_A5.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 6:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_A6.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 7:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_A7.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 8:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_A8.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 9:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_A9.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 10:
            isNarrativePlaying = false;
            runLevel1();
            currentNarationStep = 0;
            break;
    }
    currentNarationStep++;
}

void Game::runNarration2()
{
    isNarrativePlaying = true;

    moveTimer->stop();
    spawnTimer->stop();

    delete nxtLvl;
    nxtLvl = new MenuButton(this);
    nxtLvl->setGeometry(QRect(historyScene->width()-210, historyScene->height()-110, 200, 100));
    historyScene->addWidget(nxtLvl);
    nxtLvl->setText("Continuer");
    nxtLvl->show();
    connect(nxtLvl, &MenuButton::clicked, this, &Game::runNarration2, Qt::UniqueConnection);
    setScene(historyScene);

    switch (currentNarationStep) {
        case 1:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_B1.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 2:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_B2.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 3:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_B3.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 4:
            isNarrativePlaying = false;
            runLevel2();
            currentNarationStep = 0;
            break;
    }
    currentNarationStep++;
}

void Game::runNarration3()
{
    isNarrativePlaying = true;

    delete nxtLvl;
    nxtLvl = new MenuButton(this);
    nxtLvl->setGeometry(QRect(historyScene->width()-210, historyScene->height()-110, 200, 100));
    historyScene->addWidget(nxtLvl);
    nxtLvl->setText("Continuer");
    nxtLvl->show();
    connect(nxtLvl, &MenuButton::clicked, this, &Game::runNarration3, Qt::UniqueConnection);
    setScene(historyScene);

    switch (currentNarationStep) {
        case 1:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_C1.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 2:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_C2.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 3:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_C3.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 4:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_C4.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 5:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_C5.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 6:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_C6.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 7:
            isNarrativePlaying = false;
            runLevel3();
            currentNarationStep = 0;
            break;
    }
    currentNarationStep++;
}

void Game::runNarration4()
{
    isNarrativePlaying = true;
    delete nxtLvl;
    nxtLvl = new MenuButton(this);
    nxtLvl->setGeometry(QRect(historyScene->width()-210, historyScene->height()-110, 200, 100));
    historyScene->addWidget(nxtLvl);
    nxtLvl->setText("Continuer");
    nxtLvl->show();
    connect(nxtLvl, &MenuButton::clicked, this, &Game::runNarration4, Qt::UniqueConnection);
    setScene(historyScene);

    switch (currentNarationStep) {
        case 1:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_D1.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 2:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_D2.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 3:
            historyScene->setBackgroundBrush(QPixmap(":/Narration_D3.png").scaled(screenSize->width(), screenSize->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case 4:
            isNarrativePlaying = false;       
            delete nxtLvl;
            onBackToMainMenu();
            currentNarationStep = 1;
            return;
            break;
    }
    currentNarationStep++;
}

void Game::runArcade()
{
    QString path = QDir::temp().absoluteFilePath("arcadeTheme.wav");
    PlaySound((wchar_t*)path.utf16(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    isArcadeMusicPlaying = 1;
    // Hide cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // Reset weapon upgrade
    weaponNumber = 1;

    // Reset scene rect
    gameScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    gameScene->clear();
    this->viewport()->update();

    // Timers creations
    spawnTimer = new QTimer();
    moveTimer = new QTimer();
    alienShootTimer = new QTimer();
    alienShootTimer->start(AlienSpeedShootInvervalInMs);

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
    QPixmap bgPixmap = QPixmap(":/Seamless_Background3.jpg").scaledToWidth(gameScene->width());
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

    spawnTimeInterval = 2000;
    spawnTimer->start(spawnTimeInterval);
    connect(spawnTimer, &QTimer::timeout, this, &Game::onSpawnArcade, Qt::UniqueConnection);

    // Difficulty management
    difficultyTimer = new QTimer();
    difficultyTimer->start(5000); // Increase the number of aliens by 1 every 10 seconds
    connect(difficultyTimer, &QTimer::timeout,[this]()  mutable {
        // stage->setNumberOfAliens(stage->getNumberOfAliens() + 1);
        if(moveTimer->isActive()){
            if(spawnTimeInterval > 200) spawnTimeInterval -= 50;
            else spawnTimeInterval = 200;
            spawnTimer->stop();
            spawnTimer->start(spawnTimeInterval);
        }
    });

    // HUD Display
    HUDMan=new HUD(nullptr);
    gameScene->addItem(HUDMan);
    HUDMan->show();

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
    if(isNarrativePlaying) return;
    if(player == nullptr) return;

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
        }
}

void Game::keyReleaseEvent(QKeyEvent *e)
{
    // Direction
    if(e->key() == Qt::Key_Left || e->key() == Qt::Key_Right)
        if(player != nullptr) player->direction = Direction::any;
}

void Game::pauseTheGame()
{
    moveTimer->stop(); // Pause the game
    spawnTimer->stop();
    resumeButton->show();
    alienShootTimer->stop();
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
    alienShootTimer->start(AlienSpeedShootInvervalInMs);
    // Hide cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);
}

void Game::runLevel1()
{
    // Hide change level button
    nxtLvl->hide();

    // Create alien shoot timer
    alienShootTimer = new QTimer();
    alienShootTimer->start(AlienSpeedShootInvervalInMs);

    // Hide cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // Reset scene rect
    gameScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());
    gameScene->clear();

    // Timers creations
    spawnTimer = new QTimer();
    moveTimer = new QTimer();

    // Replay button connection
    connect(gameOverMenu->replayButton, &MenuButton::clicked, this, &Game::runHistory, Qt::UniqueConnection);

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
    QPixmap bgPixmap = QPixmap(":/BackGround_Lvl1.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
    gameScene->addItem(qScrollingBg);

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

    spawnTimer->start(1000);
    connect(spawnTimer, &QTimer::timeout, this, &Game::onSpawn, Qt::UniqueConnection);

    HUDMan=new HUD(nullptr);
    gameScene->addItem(HUDMan);
    HUDMan->show();

    // Scrolling background connection
    connect(moveTimer, &QTimer::timeout, this, &Game::onBackgroundScrolling, Qt::UniqueConnection);
}

void Game::runLevel2()
{
    clearGameScene();

    // Hide change level button
    nxtLvl->hide();

    // Create alien shoot timer
    alienShootTimer = new QTimer();
    alienShootTimer->start(AlienSpeedShootInvervalInMs);

    // Hide cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // Timers creations
    spawnTimer = new QTimer();
    moveTimer = new QTimer();

    // Changing for the scene game
    setScene(gameScene);

    // Background image
    qScrollingBg = new QGraphicsPixmapItem();
    QPixmap bgPixmap = QPixmap(":/BackGround_Lvl2.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
    gameScene->addItem(qScrollingBg);

    // Main timer
    moveTimer->start(1000/FPS);

    // Player creation
    player = new Player(QPixmap(":/PlayerRocket.png"), nullptr, moveTimer);
    player->setPos(width() / 2, height() - spaceShipSize.height());
    player->currentWeapon->weaponNumber = weaponNumber;
    gameScene->addItem(player);
    connect(player, &Player::sigAlienPlayerCollision, this, &Game::onAlienPlayerCollision, Qt::UniqueConnection);
    connect(player, &Player::sigDropPlayerCollision, this, &Game::onDropPlayerCollision, Qt::UniqueConnection);
    connect(this, &Game::sigPlayerShoot, this, &Game::onPlayerShoot, Qt::UniqueConnection);

    // Connection for player movements
    connect(moveTimer, &QTimer::timeout, player, &Player::onMove, Qt::UniqueConnection);

    spawnTimer->start(spawnTimeInterval);
    connect(spawnTimer, &QTimer::timeout, this, &Game::onSpawn, Qt::UniqueConnection);

    HUDMan=new HUD(nullptr);
    gameScene->addItem(HUDMan);
    HUDMan->show();

    // Change view orientation and position of elements
    HUDMan->setScore(hitCount*50,hitLive);
    rotateView(90);
    HUDMan->setRotation(-90);
    gameScene->setSceneRect(0, 0, screenSize->height(), screenSize->width());
    HUDMan->setPos(50,screenSize->width()-50);
    player->setPos(height() / 2, width() - spaceShipSize.height());

    // Scrolling background connection
    connect(moveTimer, &QTimer::timeout, this, &Game::onBackgroundScrolling, Qt::UniqueConnection);
}

void Game::runLevel3()
{
    clearGameScene();

    // Hide change level button
    nxtLvl->hide();

    // Create alien shoot timer
    alienShootTimer = new QTimer();
    alienShootTimer->start(AlienSpeedShootInvervalInMs);

    // Hide cursor
    QApplication::setOverrideCursor(Qt::BlankCursor);

    // Timers creations
    spawnTimer = new QTimer();
    moveTimer = new QTimer();

    // Changing for the scene game
    setScene(gameScene);
    gameScene->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Background image
    qScrollingBg = new QGraphicsPixmapItem();
    QPixmap bgPixmap = QPixmap(":/BackGround_Lvl3.jpg").scaledToWidth(gameScene->width());
    qScrollingBg->setPixmap(bgPixmap);
    qScrollingBg->setPos(0, -(bgPixmap.size().height() - gameScene->height()));
    gameScene->addItem(qScrollingBg);

    // Main timer
    moveTimer->start(1000/FPS);

    // Player creation
    player = new Player(QPixmap(":/PlayerRocket.png"), nullptr, moveTimer);
    player->setPos(width() / 2, height() - spaceShipSize.height());
    player->currentWeapon->weaponNumber = weaponNumber;
    gameScene->addItem(player);
    connect(player, &Player::sigAlienPlayerCollision, this, &Game::onAlienPlayerCollision, Qt::UniqueConnection);
    connect(player, &Player::sigDropPlayerCollision, this, &Game::onDropPlayerCollision, Qt::UniqueConnection);
    connect(this, &Game::sigPlayerShoot, this, &Game::onPlayerShoot, Qt::UniqueConnection);

    // Connection for player movements
    connect(moveTimer, &QTimer::timeout, player, &Player::onMove, Qt::UniqueConnection);

    spawnTimer->start(spawnTimeInterval);
    connect(spawnTimer, &QTimer::timeout, this, &Game::onSpawn, Qt::UniqueConnection);

    HUDMan=new HUD(nullptr);
    gameScene->addItem(HUDMan);
    HUDMan->show();

    // Change view orientation and position of elements
    HUDMan->setScore(hitCount*50,hitLive);
    rotateView(180);
    HUDMan->setRotation(-180);

    HUDMan->setPos(screenSize->width()-50,screenSize->height()-50);

    // Scrolling background connection
    connect(moveTimer, &QTimer::timeout, this, &Game::onBackgroundScrolling, Qt::UniqueConnection);
}

void Game::clearGameScene()
{
    // Delete timers
    moveTimer->stop();
    delete moveTimer;
    moveTimer = nullptr;
    spawnTimer->stop();
    delete spawnTimer;
    spawnTimer = nullptr;

    gameScene->clear();

    // Reset the view if it was rotated
    this->resetTransform();
    gameScene->setSceneRect(0, 0, screenSize->height(), screenSize->width());
}

void Game::increaseScore()
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
    if (hitLive <=0)
    {
        hitLive=3;
        HUDMan->reset();
        gameOver();
    }
}

void Game::onAlienPlayerCollision(Alien* pAlien)
{
    if(pAlien != nullptr)
    {
        gameScene->removeItem(pAlien);
        delete pAlien;
    }
    decreaseHealth();
}

void Game::onDropPlayerCollision(Drop* pDrop)
{
    gameScene->removeItem(pDrop);
    switch(pDrop->type)
    {
        case 1:
            if(player->currentWeapon->weaponNumber <= 3)
            {
                weaponNumber += 2;
                player->currentWeapon->weaponNumber = weaponNumber;
            }
            break;
        case 2:
            if(player->currentWeapon->weaponNumber >= 3)
            {
                weaponNumber -= 2;
                player->currentWeapon->weaponNumber = weaponNumber;
            }
            break;
        case 3:
            increaseHealth();
            break;
    }
    delete pDrop;
}

void Game::onAlienBulletCollision(Alien* pAlien, Bullet* pBullet)
{

    if(rand() % 10 == 0) // 20% chances to spawn a drop
    {

        Drop *pDrop = new Drop(dropSpeed, nullptr, moveTimer);
        connect(pDrop, &Drop::sigDropOutOfRange, this, &Game::onDropOutOfRange);
        pDrop->setPos(pAlien->pos());
        gameScene->addItem(pDrop);
    }
    increaseScore();
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
    double angle = -bulletAngle*(weaponNumber-1)/2;
    if(weaponNumber == 1)
    {angle = 0;}
    for(int i = 0; i < weaponNumber; i++)
    {
        pBullet = new Bullet(bSprite, angle, playerBulletSpeed, nullptr, moveTimer);
        pBullet->setPos(player->pos().x() + spaceShipSize.width()/2 - bulletSize.width()/2, player->pos().y() - bulletSize.height() / 2);
        gameScene->addItem(pBullet);
        connect(pBullet, &Bullet::sigBulletOutOfRange, this, &Game::onBulletOutOfRange, Qt::UniqueConnection);
        connect(pBullet, &Bullet::sigAlienBulletCollision, this, &Game::onAlienBulletCollision, Qt::UniqueConnection);
        angle += bulletAngle;
    }
}

void Game::onAlienShoot(Alien * pAlien)
{
    QPixmap bSprite(":/AmericanBullet.png");

    // Calculate angle
    double x = player->pos().x() - pAlien->pos().x();
    double y = gameScene->height() - pAlien->pos().y();
    double angle = qAtan(y/x);

    // Calculate offsets
    double offsetY = alienBulletSpeed * qSin(angle);
    double offsetX = alienBulletSpeed * qCos(angle);
    if(x < 0){
        offsetY = -offsetY;
        offsetX = -offsetX;
    }
    // Create bullet
    Bullet * pBullet = new Bullet(bSprite, offsetX, offsetY, nullptr, moveTimer);
    pBullet->setPos(pAlien->pos().x() + spaceShipSize.width()/2 - bulletSize.width()/2, pAlien->pos().y() + bulletSize.height() / 2);
    gameScene->addItem(pBullet);
    connect(pBullet, &Bullet::sigBulletOutOfRange, this, &Game::onBulletOutOfRange, Qt::UniqueConnection);
    connect(pBullet, &Bullet::sigPlayerBulletCollision, this, &Game::onPlayerBulletCollision, Qt::UniqueConnection);
}

void Game::onPlayerBulletCollision(Bullet * pBullet)
{
    if(pBullet != nullptr)
    {
        gameScene->removeItem(pBullet);
        delete pBullet;
    }
    decreaseHealth();
}

void Game::gameOver()
{
    // Reset play weapon number
    player->currentWeapon->weaponNumber = weaponNumber;

    // Change scene for game over
    setScene(gameOverMenu);

    this->resetTransform();

    // Delete timers
    delete difficultyTimer;
    difficultyTimer = nullptr;
    delete moveTimer;
    moveTimer = nullptr;
    delete spawnTimer;
    spawnTimer = nullptr;
    delete alienShootTimer;
    alienShootTimer = nullptr;

    // Delete attributes that are in gameScene
    delete player;
    player = nullptr;
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

    // Display the score
    // delete gameOverMenu->scoreText->document();
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
    currentLvl = lvl;

    historyScene->clear();
    gameScene->clear();

    // Show cursor
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

void Game::onBackgroundScrolling()
{
    if(qScrollingBg->pos().y()>=0)
    {
        spawnTimer->stop();

        // Only if all the aliens are killed
        foreach(QGraphicsItem * item, gameScene->items()){
            if(typeid(*item).name() == typeid(Alien).name()) return;
        }

        this->resetTransform();
        switch (currentLvl) {
            case 1:
                runNarration2();
                break;
            case 2:
                runNarration3();
                break;
            case 3:
                runNarration4();
                break;
        }
        currentLvl++;
        moveTimer->stop();

        // Show cursor
        QApplication::setOverrideCursor(Qt::ArrowCursor);
    }else{
        qScrollingBg->setPos(qScrollingBg->pos().x(), qScrollingBg->pos().y() + 1);
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
        case 1:
            spawnAlien(QPixmap(":/Asteroid.png"), storyAsteroidSpeed);
            break;
        case 2:
            spawnAlien(QPixmap(":/AlienShip_Lvl2.png"), storyAlienSpeed);
            break;
        case 3:
            spawnAlien(QPixmap(":/AmericanShuttle_Lvl.png"), storyShuttleSpeed);
            break;
    }
}

void Game::onSpawnArcade()
{
    int randSprite = rand()%(3);
    switch (randSprite) {
        case 0:
            spawnAlien(QPixmap(":/Asteroid2.png"), arcadeAsteroidSpeed);
            break;
        case 1:
            spawnAlien(QPixmap(":/AlienShip.png"), arcadeAlienSpeed);
            break;
        case 2:
            spawnAlien(QPixmap(":/AmericanShuttle_Lvl.png"), arcadeShuttleSpeed);
            break;
    }
}

void Game::spawnAlien(QPixmap sprite, int speed)
{
    Alien *pAlien = new Alien(sprite, nullptr, moveTimer, speed, alienShootTimer);
    int posX = rand() % int(gameScene->width() - alienSize.width());
    gameScene->addItem(pAlien);
    pAlien->setPos(posX, -alienSize.height());
    connect(pAlien, &Alien::sigAlienOutOfRange, this, &Game::onAlienOutOfRange);
    connect(pAlien, &Alien::sigAlienShoot, this, &Game::onAlienShoot);
    if(sprite.toImage() == QPixmap(":/AmericanShuttle_Lvl.png").toImage()){
        onAlienShoot(pAlien);
    }
}

void Game::onBackToMainMenu()
{
    QString path = QDir::temp().absoluteFilePath("storyTheme.wav");
    PlaySound((wchar_t*)path.utf16(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    isArcadeMusicPlaying = 0;
    // Disconnect replay button connection
    gameOverMenu->disconnectReplayButtonConnection();

    // Reset the view if it was rotated
    this->resetTransform();
    gameScene->setSceneRect(0, 0, screenSize->height(), screenSize->width());

    // Reset the scores, lives and the level
    currentLvl = lvl;
    hitCount = 0;
    hitLive = gMaxHealth;

    // Delete pause button (because gameScene->clear doesn't do it if they're attributes of Game class)
    delete backToMenuButton;
    backToMenuButton = nullptr;
    delete resumeButton;
    resumeButton = nullptr;
    delete quitButton;
    quitButton = nullptr;

    // Delete timers
    delete difficultyTimer;
    difficultyTimer = nullptr;
    delete moveTimer;
    moveTimer = nullptr;
    delete spawnTimer;
    spawnTimer = nullptr;
    delete alienShootTimer;
    alienShootTimer = nullptr;

    // Delete attributes that are in gameScene
    delete player;
    player = nullptr;
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

    if(isNarrativePlaying){
        isNarrativePlaying = false;
        nxtLvl->hide();
        delete nxtLvl;
        nxtLvl = nullptr;
        currentLvl = 1;
    }

    // Clear all scenes
    gameScene->clear();
    historyScene->clear();

    displayMainMenu();
}
