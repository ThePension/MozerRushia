#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include <QGraphicsScene>
#include <QTextDocument>
#include <QGraphicsTextItem>
#include <QTextCharFormat>
#include <QTextCursor>

#include "menubutton.h"

class GameOverMenu : public QGraphicsScene
{
public:
    GameOverMenu(QObject * parent, QSize * screenSize);
    ~GameOverMenu();

    MenuButton * quitButton;
    MenuButton * replayButton;
    MenuButton * backToMenuButton;
    QGraphicsTextItem * scoreText;
    QTextDocument * scoreTextDocument;

    void disconnectReplayButtonConnection();
};

#endif // GAMEOVERMENU_H
