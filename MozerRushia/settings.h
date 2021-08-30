#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSize>

enum Direction { any, left, right };
QSize const spaceShipSize = QSize(150, 150);
QSize const bulletSize = QSize(50, 50);
QSize const allienSize = QSize(150, 150);
int const FPS = 240;

#endif // SETTINGS_H