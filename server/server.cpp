#include "server.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>

int num_play=1;
Server::Server(QWidget *parent) : QWidget(parent)
{

    m_server=new QTcpServer(this);
    if (!m_server->listen(QHostAddress::Any, 52693)) {
        qDebug()<<"Connection failed"<<m_server->errorString();
            return;
    }
    connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));

}

void Server::newConnection(){
    while (m_server->hasPendingConnections()) {
        QString m;
        qDebug() << "sending";
        QTcpSocket *con = m_server->nextPendingConnection();
        m_clients << con;
        for(int i=0;i<m_clients.size();i++){
        m=QString ::number(i+1);
        m.append(" ");
        m.append(QChar(23));
        con->write(m.toLocal8Bit());
           }
        if(m_clients.size() == 2){
              m="2 ";
           m.append(QChar(23));
           m_clients[0]->write(m.toLocal8Bit());
        }
        if(m_clients.size() == 1){

            QString s = "8 " ;
            s.append(QChar(23));
            m_clients[0]->write(s.toLocal8Bit());
        }
        if(m_clients.size() == 2) {
            QString s = "9 ";
            s.append(QChar(23));
            m_clients[1]->write(s.toLocal8Bit());
        }

        qDebug()<<"connected to"<<m_server->serverAddress()<<"   port:  "<<52693;
        connect(con, SIGNAL(disconnected()), this, SLOT(removeConnection()));
        connect(con, SIGNAL(readyRead()), this, SLOT(newMessage()));
        qDebug() << "oomad:)";
        qDebug()<<m_clients.size();

    }
}

void Server::removeConnection(){
    if (QTcpSocket *con = qobject_cast<QTcpSocket*>(sender())) {
        m_clients.removeOne(con);
        qDebug()<<"Disconnected";
        con->deleteLater();
    }
}

void Server::newMessage()
{
    if (QTcpSocket *con = qobject_cast<QTcpSocket*>(sender())) {
        m_receivedData[con].append(con->readAll());
        if (!m_receivedData[con].contains(QChar(23)))
            return;

        QStringList messages = m_receivedData[con].split(QChar(23));
        m_receivedData[con] = messages.takeLast();
        foreach (QString message, messages) {
            //ui->log->insertPlainText("Sending message: " + message + "\n");
            message.append(QChar(23));
            foreach (QTcpSocket *socket, m_clients) {
                if (socket == con)
                    continue;
                if (socket->state() == QAbstractSocket::ConnectedState)
                    socket->write(message.toLocal8Bit());
            }
        }
    }
}
