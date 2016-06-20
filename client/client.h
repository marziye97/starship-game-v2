#ifndef CLIENT_H
#define CLIENT_H
#include <QWidget>
#include <QObject>
#include <QTcpSocket>
class client: public QWidget
{
    Q_OBJECT
public:
    explicit client(QWidget *parent = 0);

private slots:
    void connectToServer();
    void disconnectByServer();

private:
    QTcpSocket *m_socket;


};

#endif // CLIENT_H
