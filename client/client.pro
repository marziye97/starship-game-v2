#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T15:27:37
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp \
    client.cpp \
    player.cpp \
    score.cpp \
    health.cpp \
    bullet.cpp \
    enemy.cpp \
    button.cpp \
    spaceship.cpp

HEADERS  += \
    client.h \
    player.h \
    score.h \
    health.h \
    bullet.h \
    enemy.h \
    button.h \
    spaceship.h

FORMS    +=

RESOURCES += \
    pic.qrc

OTHER_FILES += \
    score.txt \
    health.txt
