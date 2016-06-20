#include <QApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    server server1;
    server1.show();
    //
    //cout << "he"

    return a.exec();
}
