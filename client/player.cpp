#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include<QGraphicsItem>
#include "client.h"

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
