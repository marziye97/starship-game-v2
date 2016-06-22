#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include<QTcpSocket>
#include<QString>
#include<QTcpServer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "player.h"
#include <QObject>
#include <QKeyEvent>
#include "score.h"
#include "health.h"

class Client : public QWidget/*,public QGraphicsView*/
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0);
    //void keyPressEvent(QKeyEvent *event);
    QGraphicsScene *scene;
    QGraphicsView *view;
    Player *player;
    Score *score;
    Health *health;
    Client *client;
signals:

public slots:

private slots:
    void keyPressEvent(QKeyEvent *event);
    void readMessage();
    void disconnectByServer();

private:
    //Ui::TcpClient *ui;
    QTcpSocket *m_socket;
    QString m_user;
    QString m_receivedData;

    void updateGui(QAbstractSocket::SocketState state);
};

#endif // CLIENT_H
