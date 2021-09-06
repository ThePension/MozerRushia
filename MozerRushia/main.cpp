#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.screens().size();
    Game gameManager(nullptr, new QSize(a.screens()[0]->size()));
    gameManager.showFullScreen();
    gameManager.displayMainMenu();
    return a.exec();
}
