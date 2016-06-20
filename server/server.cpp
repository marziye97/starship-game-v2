#include "server.h"
#include <QDebug>

server::server(QWidget *parent):QWidget(parent)
{
    m_server = new QTcpServer(this);
    if(!m_server->listen(QHostAddress::LocalHost,52690)){
            qDebug() << "connection failed";
            return;
    }
    connect(m_server,SIGNAL(newConnection()),this,SLOT(newConnection()));


}

void server::newConnection(){
    while(m_server->hasPendingConnections()){
        QTcpSocket *con = m_server->nextPendingConnection();
        m_clients << con;
        connect(con,SIGNAL(disconnected()),this,SLOT(removeConnction()));
    }
}
void server::removeConnction(){
    if(QTcpSocket *con = qobject_cast<QTcpSocket*>(sender())){
        m_clients.removeOne(con);
        con->deleteLater();
        qDebug() << "connection removed.";
    }
}
