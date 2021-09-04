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

void HUD::setScore(int newScore, int newHealth)
{
    setPlainText(QString("Health : ")+QString::number(newHealth)+"\n"+QString("Score : ")+QString::number(newScore));
}

void HUD::reset()
{
    my_Score=0;
    my_Health=gMaxHealth;
    setPlainText(QString("Health : ")+QString::number(my_Health)+"\n"+QString("Score : ")+QString::number(my_Score));
}



