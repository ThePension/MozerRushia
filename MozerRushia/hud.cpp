#include "hud.h"


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

void HUD::IncreaseScore()
{
    my_Score += 50;
    setPlainText(QString("Health : ")+QString::number(my_Health)+"\n"+QString("Score : ")+QString::number(my_Score));
}

void HUD::DecreaseHealth()
{
    my_Health --;
    setPlainText(QString("Health : ")+QString::number(my_Health)+"\n"+QString("Score : ")+QString::number(my_Score));
}

int HUD::GetHealth() const
{
    return my_Health;
}

int HUD::GetScore() const
{
    return my_Score;
}

void HUD::Reset()
{
    my_Score=0;
    my_Health=gMaxHealth;
    setPlainText(QString("Health : ")+QString::number(my_Health)+"\n"+QString("Score : ")+QString::number(my_Score));

}
