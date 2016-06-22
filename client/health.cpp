#include "health.h"
#include <QFont>


Health::Health(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    health = 7;
    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Health::decrease()
{
    health--;
    setPlainText(QString("Health: ") + QString::number(health));
}

int Health::gethealth()
{
    return health;
}
