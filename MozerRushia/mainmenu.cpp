#include "mainmenu.h"

MainMenu::MainMenu(QObject * parent, QSize * screenSize) : QGraphicsScene(parent)
{
    this->setSceneRect(0, 0, screenSize->width(), screenSize->height());

    // Creating play arcade button
    playArcadeButton = new MenuButton();
    playArcadeButton->setText("&Arcade");
    playArcadeButton->setGeometry(QRect(width() / 2 - 200, height() / 2 - 60, 400, 100));
    this->addWidget(playArcadeButton);
    playArcadeButton->show();
    playArcadeButton->setDefault(true);

    // Creation history button
    playHistoryButton = new MenuButton();
    playHistoryButton->setText("&Histoire");
    playHistoryButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 60, 400, 100));
    this->addWidget(playHistoryButton);
    playHistoryButton->show();
    playHistoryButton->setDefault(true);

    // Creating Quit button
    quitButton = new MenuButton();
    quitButton->setText("&Quitter le jeu");
    quitButton->setGeometry(QRect(width() / 2 - 200, height() / 2 + 200, 400, 100));
    this->addWidget(quitButton);
    quitButton->show();

    // Menu background image
    this->setBackgroundBrush(QPixmap(":/Fond_Menu.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

MainMenu::~MainMenu()
{
    // Delete buttons
    delete quitButton;
    quitButton = nullptr;
    delete playArcadeButton;
    playArcadeButton = nullptr;
    delete playHistoryButton;
    playHistoryButton = nullptr;
}
