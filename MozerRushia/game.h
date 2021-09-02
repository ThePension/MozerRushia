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

class Game : public QGraphicsView
{
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

    //int my_Old_Score=0;//pour tenter de garder le score a jours
    //std::string img = "Hello";


public slots:
    void onIncreaseScore();
    void onIncreaseHealth();
    void onDecreaseHealth();
    void onGameOver();
    void onChangeLevel();
    void onBackgroundScrolling();
    void onArcadeModeBackgroundScrolling();
    void onSpawn();
    void onSpawnArcade();
    void onBackToMainMenu();

private:
    Stage * stage;
    Player * player;
    QTimer * moveTimer = nullptr;
    MainMenu * mainMenuScene;
    MenuButton * nxtLvl;
    QGraphicsScene * gameScene;
    QGraphicsScene * historyScene; // will be use for the naration
    GameOverMenu * gameOverMenu;
    HUD* HUDMan = nullptr;
    QGraphicsPixmapItem * qScrollingBg;
    QGraphicsPixmapItem * qScrollingBg2;
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
