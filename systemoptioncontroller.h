#pragma once
#ifndef SYSTEMOPTIONCONTROLLER_H
#define SYSTEMOPTIONCONTROLLER_H

#include <QObject>
#include <systemoption.h>
#include <QTcpSocket>
#include <QString>

class SystemOption;

class SystemOptionController : public QObject
{
public:
    SystemOptionController(SystemOption *systemOption, QObject *parent);
    ~SystemOptionController();
private:
    QString ip;
    int port;
    QTcpSocket *socketToServer;
    SystemOption *systemOption;
    void listenClicked();
    void comButtionClicked();
    void setIpAddress();
};

#endif // SYSTEMOPTIONCONTROLLER_H
