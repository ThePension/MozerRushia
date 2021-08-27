#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.screens().size();
    Game MozerRushia(nullptr, new QSize(a.screens()[0]->size()));
    MozerRushia.showFullScreen();
    MozerRushia.run();
    return a.exec();
}
