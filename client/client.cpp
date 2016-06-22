#include "client.h"
#include<QDebug>
#include "player.h"
#include <QBrush>
#include <QImage>
#include <QKeyEvent>
#include <QWidget>
#include <QString>

Client::Client(QWidget *parent) : QWidget(parent){

    m_socket=new QTcpSocket;
    m_socket->connectToHost("0.0.0.0",52693);
    qDebug()<<"connected to"<<m_socket->localAddress()<<"   port:  "<<52693;

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    //connect(client, SIGNAL(),this,SLOT(keyPressEvent(QKeyEvent*)));
    //connect(m_socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnectByServer()));
    //connect(m_socket,SIGNAL(KeyPressEvent(QKeyEvent)),this,SLOT(KeyPressEvent(QKeyEvent)));
     scene = new QGraphicsScene();
     scene ->setSceneRect(0,0,800,600);
     view = new QGraphicsView();
     view->setBackgroundBrush(QImage(":/pic/bg.jpg"));

     view->setScene(scene);
     view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     view->setFixedSize(800,600);
     view->show();

     player = new Player();
     player->setPos(400,500);
     player->setFlag(QGraphicsItem::ItemIsFocusable);
     player->setFocus();
     scene->addItem(player);

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

    m_receivedData.append(m_socket->readAll());
    if (!m_receivedData.contains(QChar(23)))
        return;

    QStringList messages = m_receivedData.split(QChar(23));
    m_receivedData = messages.takeLast();
    foreach (const QString &message, messages) {
       player->move(message);

    }
}
void Client::keyPressEvent(QKeyEvent *event){
QString message;
        if (event->key() == Qt::Key_Left){
            message ='1' + QChar(23);
            //message ="1" ;
            //message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());
            qDebug() << "KeyPressEvent called";
            player->move("1");
            qDebug()<<"move called";
        }
        else if (event->key() == Qt::Key_Right){
            message ='2' + QChar(23);
            //message ="2" ;
            //message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());
            player->move("1");
        }
        else if (event->key() == Qt::Key_Up){
            message ='3' + QChar(23);
            //message ="3" ;
            //message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());
            player->move("1");
        }
        else if (event->key() == Qt::Key_Down){
            message ='4' + QChar(23);
            //message ="4" ;
            //message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());
            player->move("1");
        }
}

void Client::disconnectByServer(){
    m_socket->close();
}
