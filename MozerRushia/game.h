#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QTextCursor>
#include <QPixmap>
#include <QTimer>
#include <QApplication>
#include <windows.h>
#include <mmsystem.h>
#include <QDir>
#include <QDebug>
#include <QtMath>

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
    void runHistory();
    void runNarration1();
    void runNarration2();
    void runNarration3();
    void runNarration4();
    void runArcade();
    void rotateView(int rotationDegree);
    void pauseTheGame();
    void resumeTheGame();
    void runLevel1();
    void runLevel2();
    void runLevel3();
    void clearGameScene();
signals:
    void sigPlayerShoot(); // The Player shot a Bullet

public slots:
    void onBackgroundScrolling();
    void onArcadeModeBackgroundScrolling();
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
    void onAlienShoot(Alien *);
    void onPlayerBulletCollision(Bullet *);

private:
    void gameOver();
    void decreaseHealth();
    void increaseHealth();
    void spawnAlien(QPixmap, int);

    void increaseScore();

    Player * player = nullptr;
    QTimer * moveTimer = nullptr;
    MainMenu * mainMenuScene;
    MenuButton * nxtLvl = nullptr;
    QGraphicsScene * gameScene;
    QGraphicsScene * historyScene;
    GameOverMenu * gameOverMenu = nullptr;
    HUD* HUDMan = nullptr;
    QGraphicsPixmapItem * qScrollingBg;
    QGraphicsPixmapItem * qScrollingBg2 = nullptr;
    QSize * screenSize;
    QTimer * spawnTimer = nullptr;
    QTimer * difficultyTimer = nullptr;
    MenuButton * resumeButton;
    MenuButton * quitButton;
    MenuButton * backToMenuButton;
    int currentLvl=1;
    int hitCount=0;
    int hitLive=gMaxHealth;
    int spawnTimeInterval = 1000;
    int currentNarationStep = 1;
    bool isNarrativePlaying = false;

protected:
    void keyPressEvent(QKeyEvent * e) override;
    void keyReleaseEvent(QKeyEvent * e) override;
};

#endif // GAME_H
