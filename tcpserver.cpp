#include "tcpserver.h"
#include <QDebug>
#include <QRegExp>

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
    clientNum = 0;
    linkList.clear();
    setMaxPendingConnections(50);
}

/**
 * @brief TcpServer::incomingConnection
 * when incomming connection
 * if the pending socket > maxpending connection, do not connect
 * if it is repeated socket, abort the socket
 * else add it into linklist whose type is QTcpSocket*
 * connect two slots
 * emit one incomming connection signal, which wants system option receive
 * @param socketDescriptor
 */

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
#ifdef QT_DEBUG
    qDebug() << "success";
#endif
    if(linkList.size() <= maxPendingConnections())
    {
        QTcpSocket *socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);
        if(getLinkListSize(socketDescriptor) != -1)
        {
            linkList.insert(socketDescriptor, socket);
            //stringList.insert(socketDescriptor, QString(""));
            clientNum++;
            QObject::connect(socket, &QTcpSocket::stateChanged, [=](){disconnectSocket(socketDescriptor);});
            QObject::connect(socket, &QTcpSocket::readyRead, [=](){readData(socketDescriptor);});
#ifdef QT_DEBUG
            qDebug() << "success";
#endif
            emit newSocketConnected(socketDescriptor);
            //to prevent repeated socker linked
        }
        else
            socket->abort();
    }
}

/**
 * @brief TcpServer::readData
 * use the given socket descriptor, return the buffer of the socket
 * @param socketDescriptor
 */

void TcpServer::readData(qintptr socketDescriptor)
{
    qDebug() << "already in";
    QString buffer = QString(linkList[socketDescriptor]->readAll());
    qDebug() << buffer;
    /*QRegExp handle("Data.*:Rx");
    handle.setMinimal(true);
    int pos = 0;
    int handlePos = handle.indexIn(buffer);
    if(handlePos != -1)
        pos = handlePos + handle.matchedLength() - 2;*/
    QRegExp reg("Rx:NWKID:.*Finish");
    reg.setMinimal(true);
    while(buffer != "")
    {
        int pos = reg.indexIn(buffer);
        if(pos != -1)
        {
            int len = reg.matchedLength();
            QString data = buffer.left(len);
            buffer = buffer.mid(len, buffer.length() - len + 1);
            emit sendData(socketDescriptor, data);
        }
    }
    /*
     * qDebug() << temp[temp.length() - 1];
    if(temp[temp.length() - 1] == '\n')
    {
        emit sendData(socketDescriptor, stringList[socketDescriptor]);
        qDebug() << "already emit";
        stringList[socketDescriptor] = "";
    }
    qDebug() << linkList[socketDescriptor]->readAll();
    while(true)
    {
        int index = reg.indexIn(buffer, pos);
        if(index == -1)
            break;
        emit sendData(socketDescriptor, reg.cap(0));
        qDebug() << reg.cap(0);
        pos = reg.matchedLength() + index;
    }

    if(reg.indexIn(buffer) >= 0)
        emit sendData(socketDescriptor, reg.cap(0));*/
}

void TcpServer::disconnectSocket(qintptr socketDescriptor)
{
    /*
     * disconnect all slots of the socket
     * remove the socket from the linklist
     * emit a disconnect socket signal, which wants system option received
    */
    QTcpSocket *tempsocket = linkList[socketDescriptor];
    if(tempsocket->state() == QTcpSocket::UnconnectedState)
    {
        //linkList[socketDescriptor]->disconnectFromHost();
        QObject::disconnect(tempsocket);
        linkList.remove(socketDescriptor);
        qDebug()<< "Disconnect Succeed";
        clientNum--;
        emit socketDisconnected(socketDescriptor);
    }
}

int TcpServer::getLinkListSize(qintptr socketDescriptor)
{
    /*
     *if the given socket descriptor is existed in the listsize return -1;
     *else return the size of the linklist
    */
    if(linkList.contains(socketDescriptor))
        return -1;
    return linkList.size();
}

int TcpServer::getClientNum()
{
    return clientNum;
}

TcpServer::~TcpServer()
{

}
