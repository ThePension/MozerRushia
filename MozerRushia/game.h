#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QPushButton>

#include "player.h"
#include "settings.h"
#include "hud.h"
#include "mainmenu.h"
#include <QGraphicsBlurEffect>

class Game : public QGraphicsView
{
public:
    Game(QWidget * parent = 0, QSize * screenSize = 0);
    void displayMainMenu();
    void run();
    void CheckPoints();
    Player * getPlayer() { return player; }
    QTimer * getMoveTimer() { return moveTimer; }
    void pauseTheGame();
    void resumeTheGame();

public slots:
    void onIncreaseScore();
    void onDecreaseHealth();
    void onGameOver();
/**/    void onChangeLevel();
    void onBackgroundScrolling();

private:
    Player * player;
    QTimer * moveTimer;
    MainMenu * mainMenuScene;
    MenuButton * nxtLvl;
    QGraphicsScene * gameScene;
    QGraphicsScene * historyScene; // will be use for the naration
    HUD* HUDMan = nullptr;
    QGraphicsPixmapItem * qScrollingBg;
    QSize * screenSize;
    QTimer * spawnTimer;
    MenuButton * resumeButton;
    MenuButton * quitButton;

protected:
    void keyPressEvent(QKeyEvent * e) override;
    void keyReleaseEvent(QKeyEvent * e) override;
};

#endif // GAME_H
