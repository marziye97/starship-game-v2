#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QString>
#include <QGraphicsSceneMouseEvent>
class Button : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Button(/*QGraphicsItem *parent = 0,*/QString);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
public slots:

};

#endif // BUTTON_H
