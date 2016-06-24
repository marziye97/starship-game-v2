#include "health.h"
#include <QFont>
#include <QFont>
#include <QFile>
#include <QString>
#include <QTextStream>
#include<sstream>
#include<string>
#include <QDebug>

Health::Health(QGraphicsItem *parent):QGraphicsTextItem(parent)
{

    QFile healthfile("/home/mary/Documents/qt/starship/health.txt");
    if(!healthfile.exists())
        qDebug()<<"doesn't exist";
    if(!healthfile.open(QFile::ReadOnly|QFile::Text)){
        return;
    }
    QTextStream in(&healthfile);
    QString s = in.readAll();
    health = s.split(" ")[0].toInt();
    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
}

void Health::decrease()
{
    health--;
    QFile healthfile("/home/mary/Documents/qt/starship/health.txt");
    if(!healthfile.exists())
        qDebug()<<"doesn't exist";
    if(!healthfile.open(QFile::WriteOnly|QFile::Text)){
        return;
    }
    QTextStream out(&healthfile);
    out << QString::number(health);
    qDebug() << health;
    setPlainText(QString("Health: ") + QString::number(health));
}

int Health::gethealth()
{
    return health;
}
