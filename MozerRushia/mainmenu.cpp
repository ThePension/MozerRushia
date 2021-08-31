#include "mainmenu.h"

MainMenu::MainMenu(QObject * parent, QSize * screenSize) : QGraphicsScene(parent)
{
    this->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Creating Quit button
    quitButton = new MenuButton();
    quitButton->setText("Quitter le jeu");
    quitButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 75, 400, 100));
    this->addWidget(quitButton);
    quitButton->show();

    // Creating play button
    playButton = new MenuButton();
    playButton->setText("Jouer");
    playButton->setGeometry(QRect(width() / 2 - 200, height() / 2 - 75, 400, 100));
    this->addWidget(playButton);
    playButton->show();
    playButton->setDefault(true);

    // Menu background image
    this->setBackgroundBrush(QPixmap(":/Fond_Menu.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
