#include "hud.h"
/**/ // pas mal de tri a refaire dans cette classe

HUD::HUD(QGraphicsItem *parent) :QGraphicsTextItem(parent)
{
    setPlainText(QString("Health : ")+QString::number(my_Health)+"\n"+QString("Score : ")+QString::number(my_Score));
    QFont HUDFont("comic sans", 30);
    setFont(HUDFont);
    setDefaultTextColor(Qt::red);
    int txPos = 50;
    int tyPos = 50;
    setPos(txPos,tyPos);
}


HUD::~HUD()
{

}

void HUD::increaseScore()
{
    my_Score += 50;
    setPlainText(QString("Health : ")+QString::number(my_Health)+"\n"+QString("Score : ")+QString::number(my_Score));
}

void HUD::decreaseHealth()
{
    my_Health --;
    setPlainText(QString("Health : ")+QString::number(my_Health)+"\n"+QString("Score : ")+QString::number(getScore()));
}

void HUD::setScore(int newScore, int newHealth)
{
    setPlainText(QString("Health : ")+QString::number(newHealth)+"\n"+QString("Score : ")+QString::number(newScore));
}

int HUD::getHealth() const
{
    return my_Health;
}

int HUD::getScore() const
{
    return my_Score;
}

void HUD::reset()
{
    my_Score=0;
    my_Health=gMaxHealth;
    setPlainText(QString("Health : ")+QString::number(my_Health)+"\n"+QString("Score : ")+QString::number(my_Score));

}



