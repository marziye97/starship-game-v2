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
#include "button.h"

class Client : /*public QWidget,*/public QGraphicsView
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *event);
    QGraphicsScene *scene;
    QGraphicsView *view;
    Player *player;
    Score *score;
    Health *health;
    Button *play;
    void menu();
    void gameOver();
    void makeplayer(int);
    void movePlayer(int,QString);
public slots:
    void start();


private slots:
    //void keyPressEvent(QKeyEvent *event);
    void readMessage();
    void disconnectByServer();

private:
    //Ui::TcpClient *ui;
    QTcpSocket *m_socket;
    QString m_receivedData;

};

#endif // CLIENT_H
