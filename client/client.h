#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include<QTcpSocket>
#include<QString>
#include<QTcpServer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "player.h"

class Client : public QWidget/*,public QGraphicsView*/
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0);
    QGraphicsScene *scene;
    QGraphicsView *view;
    Player *player;
signals:

public slots:

private slots:
    //void on_text_returnPressed();
    void readMessage();
    //void on_connect_clicked();
    //void connectedToServer();
    //void on_disconnect_clicked();
    void disconnectByServer();

private:
    //Ui::TcpClient *ui;
    QTcpSocket *m_socket;
    QString m_user;
    QString m_receivedData;

    void updateGui(QAbstractSocket::SocketState state);
};

#endif // CLIENT_H
