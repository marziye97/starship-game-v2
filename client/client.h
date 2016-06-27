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
#include <QVector>
#include <vector>
class Client : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *event);
    QGraphicsScene *scene;
    QGraphicsView *view;
    Player *player1;
    Player *player2;
    QVector <Player*> players;
    Score *score;
    Health *health;
    Button *play;
    void menu();
    void gameOver();
    void makeplayer(int);
    void movePlayer(int,int);
public slots:
    void start();

signals:
    //void keyPressEvent(QKeyEvent *event);

private slots:
    void readMessage();
    void disconnectByServer();

private:
    QTcpSocket *m_socket;
    QString m_receivedData;

};

#endif // CLIENT_H
