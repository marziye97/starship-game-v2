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
#include <QTimer>
using namespace std;

int player_num= 0;
int result=0;
int client_num=1;

Client::Client(QWidget *parent) {

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

//    QTimer *timer = new QTimer();
//    QObject::connect(timer,SIGNAL(timeout()),player1,SLOT(spawn()));

//    timer->start(2000);

}
void Client::menu(){
    play = new Button(QString(":/pic/playbutton.png"));
    play->setPos(300,300);
    connect(play,SIGNAL(clicked()),this,SLOT(start()));

}

void Client::makeplayer(int num)
{
    if(num == 1&&result==0){
        player1 = new Player();
        players.push_back(player1);
        player1->setPos(300,500);
        player1->setFlag(QGraphicsItem::ItemIsFocusable);
        player1->setFocus();
        //player1->grabKeyboard();
        scene->addItem(player1);
        result=1;
        QTimer *timer = new QTimer();
        QObject::connect(timer,SIGNAL(timeout()),players[0],SLOT(spawn()));

        timer->start(2000);

    }
    else if(num==2){

        player2 = new Player();
        players.push_back(player2);
        player2->setPos(600,500);
        scene->addItem(player2);
        QTimer *timer = new QTimer();
        QObject::connect(timer,SIGNAL(timeout()),player2,SLOT(spawn()));

        timer->start(2000);
    }

}

void Client::movePlayer(int num,int mov)
{
    QString a;
    if (mov == 3)
        a = "1";
    if (mov == 4)
        a = "2";
    if (mov == 5)
        a = "3";
    if (mov == 6)
        a = "4";

    qDebug()<<"num ="<<num;
    if(num==1){
    players[1]->move(a);
    }
    else if(num==2){
        players[0]->move(a);
    }


}
void Client::start(){
    scene->removeItem(play);
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
        qDebug()<<"message: "<<message ;
        qDebug()<<"messages"<<messages;
       if(a == 1 || a == 2){
//           makeplayer(client_num++);
           qDebug()<<"oomad";
           makeplayer(a);
           qDebug()<<"oomad";


            qDebug() << "raft";
       }
       else if(a == 8 && !player_num) {
           //player_num=2;
           player_num = 1;
           players[0]->number = 1;
       }
       else if(a == 9 && !player_num){
           //player_num = 1;
           player_num = 2;
           players[1]->number = 2;

       }
       else if(message == "3 1 " ||message == "3 2 " || message == "4 1 " ||message == "4 2 " || message == "5 1 " ||message == "5 2 " || message == "6 1 "||message == "6 2 " ) {
           qDebug()<<"kheili khari";
           //QString mn=messages.takeLast();
           //qDebug()<<":)"<<mn<<" "<<messages;

           string str = message.toStdString();
           stringstream ss(str);
           int a, b;
           ss >> a >> b;
           qDebug()<<"a="<<a<<"B="<<b;
           movePlayer(b,a);

       }
    }
}
void Client::keyPressEvent(QKeyEvent *event){
    qDebug() << player_num;
QString message;
        if (event->key() == Qt::Key_Left){
             message ="3 " ;
            if(player_num == 1){
                players[0]->move("1");
                message.append("2 ");
            }
            else if(player_num == 2){
                players[1]->move("1");
                message.append("1 ");
            }

            message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());

        }
        else if (event->key() == Qt::Key_Right){
            message ="4 " ;
            if(player_num == 1){
                players[0]->move("2");
                message.append("2 ");
            }
            else if(player_num == 2){
                players[1]->move("2");
            message.append("1 ");
            }
            message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());

        }
        else if (event->key() == Qt::Key_Up){
            message ="5 " ;
            qDebug() << "up";
            if(player_num == 1){
                players[0]->move("3");
            message.append("2 ");
            }
            else if(player_num == 2){
                players[1]->move("3");
            message.append("1 ");
            }
            message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());
        }
        else if (event->key() == Qt::Key_Down){
            message ="6 " ;
            qDebug() << "down";
            if(player_num == 1){
                players[0]->move("4");
            message.append("2 ");
            }
            else if(player_num == 2){
                players[1]->move("4");
            message.append("1 ");
            }

            message.push_back( QChar(23));
            m_socket->write(message.toLocal8Bit());

        }
}

void Client::disconnectByServer(){
    m_socket->close();
}
