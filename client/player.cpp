#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include<QGraphicsItem>
#include "client.h"
#include "spaceship.h"

Spaceship * ship;
extern Client* client;
Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    //set the picture of player.....

    setPixmap(QPixmap(":/pic/player.png"));
}


void Player::move(QString message){
    if(message=="1"){
        if (pos().x() > 0)
       setPos(x()-10,y());
    }
     if(message=="2"){
         if(pos().x()+100 <800)
         setPos(x()+10 , y());

     }
     if(message=="3"){
         if(pos().y() >  0)
         setPos(x() , y()-10);
     }
      if(message=="3"){
          if(pos().y()+100 <600)
          setPos(x() , y()+10);
      }

}

void Player::spawn(){
    qDebug()<<"come in spawn";
    // create an spaceship
//    if(game->level->getlevel() >= 3 ){
//        Bubble1 *bubble1 = new Bubble1();
//        scene()->addItem(bubble1);
//        Bubble2 *bubble2 = new Bubble2();
//        scene()->addItem(bubble2);
        ship = new Spaceship();
        scene()->addItem(ship);
    //}
//    else if(game->level->getlevel() <=2){
//        ship = new Spaceship();
//        scene()->addItem(ship);
//    }
}
