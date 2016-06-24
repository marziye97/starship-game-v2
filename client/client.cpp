#include "client.h"
#include<QDebug>
#include "player.h"
#include <QBrush>
#include <QImage>
#include <QKeyEvent>
#include <QWidget>
#include <QString>
#include <QtCore>
#include<typeinfo>
#include <sstream>

using namespace std;

int result=0;
int client_num=1;
Client::Client(QWidget *parent) /*: QWidget(parent)*/{

    m_socket=new QTcpSocket;
    m_socket->connectToHost("0.0.0.0",52693);
    //qDebug()<<"connected to"<<m_socket->localAddress()<<"   port:  "<<52693;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(m_socket,SIGNAL(connected()),this,SLOT(readMessage()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnectByServer()));

    scene = new QGraphicsScene();
    scene ->setSceneRect(0,0,1000,900);
    setBackgroundBrush(QImage(":/pic/bg.jpg"));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1000,900);

     //setFocus();

}
void Client::menu(){
    play = new Button(QString(":/pic/playbutton.png"));
    play->setPos(300,300);
    scene->addItem(play);
    connect(play,SIGNAL(clicked()),this,SLOT(start()));

}

void Client::makeplayer(int num)
{
    if(num == 1&&result==0){
        player = new Player();
        player->setPos(300,500);
        player->setFlag(QGraphicsItem::ItemIsFocusable);
        player->setFocus();
        scene->addItem(player);
        result=1;
    }
    else if(num==2){
        player = new Player();
        player->setPos(600,500);
        player->setFlag(QGraphicsItem::ItemIsFocusable);
        player->setFocus();
        scene->addItem(player);
    }

}

void Client::movePlayer(int num,QString message)
{
       if(num ==1){
           player->move(message);
       }
       else if(num == 2){
           player->move(message);
       }

}
void Client::start(){
    scene->removeItem(play);
//    player = new Player();
//    player->setPos(400,500);
//    player->setFlag(QGraphicsItem::ItemIsFocusable);
//    player->setFocus();
//    scene->addItem(player);

    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);
}

void Client::readMessage(){
    if (m_socket->state() != QAbstractSocket::ConnectedState){
        qDebug()<<"There isnt any connection";
        return;
    }
    qDebug()<<"connected to"<<m_socket->localAddress()<<"   port:  "<<52693;
    qDebug() << "heyy1";
    m_receivedData.append(m_socket->readAll());
    if (!m_receivedData.contains(QChar(23)))
        return;
    qDebug() << "heyy1";
    QStringList messages = m_receivedData.split(QChar(23));
    m_receivedData = messages.takeLast();
    qDebug() << "heyy2";
    foreach (const QString &message, messages) {
        string str = message.toStdString();
        stringstream ss(str);
        int a;
        ss >> a;
        qDebug() << "heyy3";
        //messages = messages.join("\n").toStdString();
        qDebug()<<typeid(messages.at(0)).name();
       if(message == "5 "){
           qDebug()<<"oomad";
            makeplayer(client_num++);
            qDebug() << "raft";
       }
       if(message == "1 " || message == "3 " || message == "2 " || message == "4 ")
            movePlayer(client_num++,message);
    }
}
void Client::keyPressEvent(QKeyEvent *event){
QString message;
        if (event->key() == Qt::Key_Left){
            player->move("1");
            //message ='1 ' + QChar(23);
            message ="1" ;
            message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());

        }
        else if (event->key() == Qt::Key_Right){
//            message ='2 ' + QChar(23);
            message ="2" ;
            message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());
            player->move("2");
        }
        else if (event->key() == Qt::Key_Up){
//            message ='3 ' + QChar(23);
            message ="3" ;
            message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());
            player->move("3");
        }
        else if (event->key() == Qt::Key_Down){
//            message ='4 ' + QChar(23);
            message ="4" ;
            message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());
            player->move("4");

        }
}

void Client::disconnectByServer(){
    m_socket->close();
}
