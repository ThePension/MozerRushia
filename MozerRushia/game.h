#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QPushButton>
#include <QTextCursor>
// #include <Q

#include "player.h"
#include "settings.h"
#include "hud.h"
#include "mainmenu.h"
#include "gameovermenu.h"
#include "bullet.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent = 0, QSize * screenSize = 0);
    void displayMainMenu();
    void run();
    void runLvl1();
    void runLvl2();
    void runLvl3();
    void runNarr1();
    void runNarr2();
    void runNarr3();
    void runNarr4();
    void runArcade();
    void rotateView(int rotationDegree);
    void pauseTheGame();
    void resumeTheGame();
signals:
    void sigPlayerShoot(); // The Player shot a Bullet

public slots:
    void onChangeLevel();
    void onBackgroundScrolling();
    void onArcadeModeBackgroundScrolling();
    void onNarrationScrolling();
    void onSpawn();
    void onSpawnArcade();
    void onBackToMainMenu();
    void onAlienPlayerCollision(Alien*); // An Alien got to the Player
    void onDropPlayerCollision(Drop*);  // A Drop got to the Player
    void onAlienBulletCollision(Alien*, Bullet*); // A Bullet got to an Alien
    void onAlienOutOfRange(Alien*); // An Alien went out of the screen
    void onBulletOutOfRange(Bullet*); // A Bullet went out of the screen
    void onDropOutOfRange(Drop*); // A Drop went out of the screen
    void onPlayerShoot(); // The Player shot a Bullet

private:
    void gameOver();
    void decreaseHealth();
    void increaseHealth();
    void spawnAlien(QPixmap);

    void increaseScore();

    Player * player;
    QTimer * moveTimer = nullptr;
    QTimer * narTimer = nullptr;
    MainMenu * mainMenuScene;
    MenuButton * nxtLvl = nullptr;
    QGraphicsScene * gameScene;
    QGraphicsScene * narrationScene;
    QGraphicsScene * historyScene;
    GameOverMenu * gameOverMenu;
    HUD* HUDMan = nullptr;
    QGraphicsPixmapItem * qScrollingNar;
    QGraphicsPixmapItem * qScrollingBg;
    QGraphicsPixmapItem * qScrollingBg2 = nullptr;
    QSize * screenSize;
    QTimer * spawnTimer = nullptr;
    QTimer * difficultyTimer = nullptr;
    MenuButton * resumeButton;
    MenuButton * quitButton;
    MenuButton * backToMenuButton;
    int currentLvl=lvl;
    int hitCount=0;
    int hitLive=gMaxHealth;
    int spawnTimeInterval = 3000;

protected:
    void keyPressEvent(QKeyEvent * e) override;
    void keyReleaseEvent(QKeyEvent * e) override;
};

#endif // GAME_H
