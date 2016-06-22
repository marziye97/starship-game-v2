#include "client.h"
#include<QDebug>
#include "player.h"
#include <QBrush>
#include <QImage>

Client::Client(QWidget *parent) : QWidget(parent){
     scene = new QGraphicsScene();
     scene ->setSceneRect(0,0,1376,800);
     view = new QGraphicsView();
     view->setBackgroundBrush(QImage(":/pic/bg.jpg"));

     view->setScene(scene);
     view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     view->setFixedSize(1376,800);
     view->show();

     player = new Player();
     player->setPos(400,500);
     player->setFlag(QGraphicsItem::ItemIsFocusable);
     player->setFocus();
     scene->addItem(player);

      m_socket=new QTcpSocket;
      m_socket->connectToHost("0.0.0.0",52693);
      qDebug()<<"connected to"<<m_socket->localAddress()<<"   port:  "<<52693;

      connect(m_socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
      //connect(m_socket, SIGNAL(connected()), this, SLOT(connectedToServer()));
      connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnectByServer()));

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
        //ui->chat->insertPlainText(message + "\n");

    }
}

void Client::disconnectByServer(){
    m_socket->close();
}
