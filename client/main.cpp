#include <QApplication>
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client1;
    //client1.show();

    return a.exec();
}
