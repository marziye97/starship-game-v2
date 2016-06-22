#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
//hmmmmm
class Player : public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent = 0 );
    void move(QString);
};
#endif
