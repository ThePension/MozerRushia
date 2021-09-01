#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSize>
#include <QTimer>

enum Direction { any, left, right };
QSize const spaceShipSize = QSize(120, 150);
QSize const bulletSize = QSize(50, 50);
QSize const alienSize = QSize(150, 150);

int const FPS = 144;
int const gMaxHealth = 3;
int const lvl=1;

#endif // SETTINGS_H
