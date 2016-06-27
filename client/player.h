#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Player : public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent = 0 );
    int number;
public slots:
    void move(QString);
    void spawn();
signals:
   // void keyPressEvent(QKeyEvent *event);


};
#endif
