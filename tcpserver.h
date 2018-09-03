#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMap>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = nullptr);
    ~TcpServer();
    QMap<qintptr, QTcpSocket*> linkList;
    //QMap<qintptr, QString> stringList;
    int getClientNum();
private:
    int clientNum;
signals:
    void newSocketConnected(int socketDescriptor);
    void socketDisconnected(int socketDescriptor);
    void sendData(int socketDescriptor, QString data);
protected:
    int getLinkListSize(qintptr socketDescriptor);
    void incomingConnection(qintptr socketDescriptr) override;
    void disconnectSocket(qintptr socketDescriptor);
    void readData(qintptr socketDescriptor);
};

#endif // TCPSERVER_H
