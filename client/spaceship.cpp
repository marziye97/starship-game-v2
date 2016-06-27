#include "spaceship.h"
#include <QGraphicsScene>
#include "client.h"
#include <QList>
#include <typeinfo>
#include <stdlib.h>
#include <QDebug>

extern Client * client;

Spaceship::Spaceship(QGraphicsItem *parent):Enemy(parent)
{
    power=20;
    int random_number = rand() % 700;
    setPos(random_number,0);
    setPixmap(QPixmap(":/pic/ship.gif"));
}

int Spaceship::getpower()
{
    return power;
}

//void Spaceship::setpower(int npower)
//{
//    power =power - npower;
//   qDebug()<<power;
//}
void Spaceship::move(){
    /*QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Player)){
            client->health->decrease();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }*/

    setPos(x(),y()+5);

    if (pos().y() > 900){
        scene()->removeItem(this);
        delete this;
    }
}

