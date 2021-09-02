#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QPushButton>
#include <QTextCursor>

#include "player.h"
#include "settings.h"
#include "hud.h"
#include "mainmenu.h"
#include "stage.h"
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
    void runArcade();
    void rotateView(int rotationDegree);
    void CheckPoints();
    Player * getPlayer() { return player; }
    QTimer * getMoveTimer() { return moveTimer; }
    void pauseTheGame();
    void resumeTheGame();
signals:
    void sigPlayerShoot(); // The Player shot a Bullet

public slots:
    void onIncreaseScore();
    //void onGameOver();
    void onChangeLevel();
    void onBackgroundScrolling();
    void onArcadeModeBackgroundScrolling();
    void onSpawn();
    void onSpawnArcade();
    void onAlienPlayerCollision(Alien*); // An Alien got to the Player
    void onDropPlayerCollision(Drop*);  // A Drop got to the Player
    void onAlienBulletCollision(Alien*, Bullet*); // A Bullet got to an Alien
    void onAlienOutOfRange(Alien*); // An Alien went out of the screen
    void onBulletOutOfRange(Bullet*); // A Bullet went out of the screen
    void onDropOutOfRange(Drop*); // A Drop went out of the screen
    void onPlayerShoot(); // The Player shot a Bullet



private:
    void onGameOver();
    void decreaseHealth();
    void increaseHealth();
    void spawnArcade(QPixmap);
    Stage * stage;
    Player * player;
    QTimer * moveTimer;
    MainMenu * mainMenuScene;
    MenuButton * nxtLvl;
    QGraphicsScene * gameScene;
    QGraphicsScene * historyScene; // will be use for the naration
    GameOverMenu * gameOverMenu;
    HUD* HUDMan = nullptr;
    QGraphicsPixmapItem * qScrollingBg;
    QGraphicsPixmapItem * qScrollingBg2;
    QSize * screenSize;
    QTimer * spawnTimer;
    MenuButton * resumeButton;
    MenuButton * quitButton;
    int currentLvl=lvl;
    int hitCount=0;
    int hitLive=gMaxHealth;

protected:
    void keyPressEvent(QKeyEvent * e) override;
    void keyReleaseEvent(QKeyEvent * e) override;
};

#endif // GAME_H
