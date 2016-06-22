#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include<QGraphicsItem>
#include "client.h"

extern Client* client;
Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    //set the picture of player.....

    setPixmap(QPixmap(":/pic/player.jpeg"));
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
        setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if(pos().x()+100 <800)
        setPos(x()+10 , y());
    }
    else if (event->key() == Qt::Key_Up){
        if(pos().y() >  0)
        setPos(x() , y()-10);
    }
    else if (event->key() == Qt::Key_Down){
        if(pos().y()+100 <600)
        setPos(x() , y()+10);
    }
}
