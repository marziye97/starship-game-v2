#include "server.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
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
        QTcpSocket *con = m_server->nextPendingConnection();
        m_clients << con;
        qDebug()<<"connected to"<<m_server->serverAddress()<<"   port:  "<<52693;
        connect(con, SIGNAL(disconnected()), this, SLOT(removeConnection()));
        connect(con, SIGNAL(readyRead()), this, SLOT(newMessage()));
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
