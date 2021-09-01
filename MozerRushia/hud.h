#ifndef HUD_H
#define HUD_H

#include "settings.h"

#include <QGraphicsSimpleTextItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QApplication>

class HUD: public QGraphicsTextItem
{
public:
    HUD(QGraphicsItem* parent=nullptr);
    ~HUD();

    void IncreaseScore();
    void DecreaseHealth();
    void Reset();

    int GetHealth() const;
    int GetScore() const;

private:
    int my_Health = gMaxHealth;
    int my_Score = 0;
};

#endif // HUD_H
