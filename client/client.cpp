#include "client.h"

client::client(QWidget *parent):QWidget(parent)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket,SIGNAL(connected()),this,SLOT(connectToServer()));
    connect(m_socket,SIGNAL(disconnected()),this,SLOT(disconnectByServer()));

}
void client::connectToServer(){
    QAbstractSocket::ConnectedState;
}
void client::disconnectByServer(){
    QAbstractSocket::UnconnectedState;
}
