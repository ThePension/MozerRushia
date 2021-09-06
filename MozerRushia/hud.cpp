#include "hud.h"

HUD::HUD(QGraphicsItem *parent) :QGraphicsTextItem(parent)
{
    setPlainText(QString("PV : ")+QString::number(my_Health)+"\n"+QString("Score : ")+QString::number(my_Score));
    QFont HUDFont("comic sans", 30);
    setFont(HUDFont);
    setDefaultTextColor(Qt::red);
    int txPos = 50;
    int tyPos = 50;
    setPos(txPos,tyPos);
    setZValue(1);
}

HUD::~HUD()
{

}

void HUD::setScore(int newScore, int newHealth)
{
    setPlainText(QString("PV : ")+QString::number(newHealth)+"\n"+QString("Score : ")+QString::number(newScore));
}

void HUD::reset()
{
    my_Score=0;
    my_Health=gMaxHealth;
    setPlainText(QString("PV : ")+QString::number(my_Health)+"\n"+QString("Score : ")+QString::number(my_Score));
}



