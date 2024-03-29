#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSize>
#include <QTimer>

enum Direction { any, left, right };
QSize const spaceShipSize = QSize(120, 150);
QSize const bulletSize = QSize(50, 50);
QSize const alienSize = QSize(150, 150);
QSize const dropSize = QSize(50, 50);

int const FPS = 144;
int const gMaxHealth = 3;
int const lvl = 1;
double const bulletAngle = 0.5;
int const playerBulletSpeed = -5;
int const alienBulletSpeed = 8;
int const dropSpeed = 3;
int const arcadeAlienSpeed = 3;
int const arcadeAsteroidSpeed = 1;
int const arcadeShuttleSpeed = 2;
int const storyAlienSpeed = 6;
int const storyAsteroidSpeed = 2;
int const storyShuttleSpeed = 3;
int const AlienSpeedShootInvervalInMs = 1000;

#endif // SETTINGS_H
