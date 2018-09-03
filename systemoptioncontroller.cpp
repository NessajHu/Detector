#include "systemoptioncontroller.h"
#include "QDebug"
#include "QMessageBox"
#include "QNetworkInterface"
#include "QList"

SystemOptionController::SystemOptionController(SystemOption *systemOption, QObject *parent) :
    QObject(parent),
    systemOption(systemOption)
{
    socketToServer = new QTcpSocket(this);
    QObject::connect(systemOption->listen, &QPushButton::clicked, this, &SystemOptionController::listenClicked);
    QObject::connect(systemOption->comButton, &QPushButton::clicked, this, &SystemOptionController::comButtionClicked);
    setIpAddress();
}

void SystemOptionController::setIpAddress()
{
    QString ip;
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();
    foreach(QHostAddress tempIp, ipList)
    {
        if(tempIp != QHostAddress::LocalHost && tempIp.toIPv4Address())
        {
            ip = tempIp.toString();
            break;
        }
    }
    systemOption->getIp->setText(ip);
}

void SystemOptionController::listenClicked()
{

}

void SystemOptionController::comButtionClicked()
{

}

SystemOptionController::~SystemOptionController()
{

}
