#include "button.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "client.h"

extern Client *client;
Button::Button(/*QGraphicsItem *parent,*/QString pic)

{
    setPixmap(QPixmap(pic));
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}
