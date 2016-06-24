#ifndef SERVER_H
#define SERVER_H
#include <QWidget>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class Server:public QWidget
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = 0);

private slots:
   void newConnection();
   void removeConnection();
   void newMessage();


   private:
       QTcpServer *m_server;
       QList<QTcpSocket*> m_clients;
       QHash<QTcpSocket*, QString> m_receivedData;

};

#endif // SERVER_H
