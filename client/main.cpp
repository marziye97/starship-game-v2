#include <QApplication>
#include "client.h"
Client *client;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Client client;
    client = new Client();
    client->show();
    client->menu();
    //client.show();
    return a.exec();
}
