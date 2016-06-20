#ifndef SERVER_H
#define SERVER_H
#include <QWidget>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class server:public QWidget
{
    Q_OBJECT
public:
    explicit server(QWidget *parent = 0);

private slots:
   void newConnection();
   void removeConnction();

private:
   QTcpServer *m_server;
   QList<QTcpSocket*> m_clients;

};

#endif // SERVER_H
