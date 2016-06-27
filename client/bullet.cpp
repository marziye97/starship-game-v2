#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include "spaceship.h"

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/pic/bullet.jpeg"));
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);

}

void Bullet::move(){
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Spaceship)){
            //if(power1 == ship->getpower()){
               // game->score->increase();
//                int random_numbetr= (rand()%2)+1;
//                if(random_numbetr == 1){
//                    Award1 * award1 = new Award1();
//                    award1->setPos(x(),y());
//                    scene()->addItem(award1);
//                }
//                else if(random_numbetr == 2){
//                    Award2 * award2 = new Award2();
//                    award2->setPos(x(),y());
//                    scene()->addItem(award2);
//                }
                scene()->removeItem(colliding_items[i]);
                delete colliding_items[i];
            //}
            //else if(power1 != ship->power){
                scene()->removeItem(this);
                delete this;
                //ship->setpower(power1);
                //return;
            //}
            /*scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];*/

            return;
        }
    }
    setPos(x(),y()-10);
    if (pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }

}
