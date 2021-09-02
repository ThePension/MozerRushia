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

    void increaseScore();
    void decreaseHealth();
    void reset();

    void setScore(int newScore,int newHealth);
    void setHealth(int newHealth);

    int getHealth() const;
    int getScore() const;

private:
    int my_Health = gMaxHealth;
    int my_Score=0;
    //int my_Old_Score=getScore();
};

#endif // HUD_H
