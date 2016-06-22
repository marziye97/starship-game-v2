#ifndef ENEMY_H
#define ENEMY_H
#include <QObject>
#include <QGraphicsPixmapItem>

class Enemy:public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(QGraphicsItem * parent=0);
public slots:
    virtual void move() = 0;
};


#endif // ENEMY_H
