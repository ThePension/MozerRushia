#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsScene>

#include "menubutton.h"

class MainMenu : public QGraphicsScene
{
    Q_OBJECT
public:
    MainMenu(QObject * parent, QSize * screenSize);
    ~MainMenu();

    MenuButton * quitButton;
    MenuButton * playButton;
    // MenuButton * settingsButton;
};

#endif // MAINMENU_H
