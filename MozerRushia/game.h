#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QKeyEvent>

#include "player.h"
#include "settings.h"

class Game : public QGraphicsView
{
public:
    Game(QWidget * parent = 0, QSize * screenSize = 0);
    void run();
private:
    Player * player;
protected:
    void keyPressEvent(QKeyEvent * e) override;
    void keyReleaseEvent(QKeyEvent * e) override;
};

#endif // GAME_H
