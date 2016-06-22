#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include "player.h"
#include "client.h"

extern Client * client;

Enemy::Enemy(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent)
{
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
}
