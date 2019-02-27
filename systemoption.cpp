#include "systemoption.h"
#include <QDebug>
#include <QIntValidator>
#include <QString>
#include <QTimer>
#include <QVariant>

SystemOption::SystemOption(QWidget *parent) :
    QWidget(parent),
    comLabel(new QLabel(this)),
    comComboBox(new QComboBox(this)),
    baudRateLabel(new QLabel(this)),
    baudRateComboBox(new QComboBox(this)),
    comButton(new QPushButton(this)),
    comStatusLabel(new QLabel(this)),
    comStatus(new QLabel(this)),
    ipLabel(new QLabel(this)),
    portLabel(new QLabel(this)),
    getIp(new QLineEdit(this)),
    getPort(new QLineEdit(this)),
    listen(new QPushButton(this)),
    linkStatusLabel(new QLabel(this)),
    linkStatus(new QComboBox(this)),
    serverStatusLabel(new QLabel(this)),
    serverStatus(new QLabel(this)),
    server(new TcpServer(this)),
    systemOptionLayout(new QGridLayout(this))
{
    setWindowTitle("System Option");
    resize(300, 240);
    comLabel->setText("COM");
    comComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    baudRateLabel->setText("Baud Rate");
    baudRateComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    comButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    comButton->setText("Open COM");
    comStatusLabel->setText("COM Status");
    comStatus->setText("Unconnected");
    ipLabel->setText("IP Address");
    portLabel->setText("Port");
    getIp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    getIp->setFocusPolicy(Qt::NoFocus);
    QObject::connect(server, &TcpServer::newSocketConnected, this, &SystemOption::comboBoxAddItem);
    QObject::connect(server, &TcpServer::newSocketConnected, [&](){serverStatus->setText("Connecting");});
    QObject::connect(server, &TcpServer::socketDisconnected, this, &SystemOption::comboBoxDeleteItem);
    QObject::connect(server, &TcpServer::socketDisconnected, [&](){serverStatus->setText("Listening Port" + QString::number(port));});
    getPort->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    QIntValidator *getPortValidator = new QIntValidator(0, 65535, getPort);
    getPort->setValidator(getPortValidator);
    listen->setText("Listen");
    listen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    linkStatusLabel->setText("Link to");
    serverStatusLabel->setText("Sever Status");
    serverStatus->setText("Unconnected");
    systemOptionLayout->addWidget(comLabel, 0, 0, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(baudRateLabel, 0, 1, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(comComboBox, 1, 0, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(baudRateComboBox, 1, 1, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(comButton, 1, 2, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(comStatusLabel, 2, 0, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(comStatus, 2, 1, 1, 2, Qt::AlignVCenter);
    systemOptionLayout->addWidget(ipLabel, 3, 0, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(portLabel, 3, 1, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(getIp, 4, 0, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(getPort, 4, 1, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(listen, 4, 2, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(linkStatusLabel, 5, 0, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(linkStatus, 5, 1, 1, 2, Qt::AlignVCenter);
    systemOptionLayout->addWidget(serverStatusLabel, 6, 0, 1, 1, Qt::AlignVCenter);
    systemOptionLayout->addWidget(serverStatus, 6, 1, 1, 2, Qt::AlignVCenter);
    //systemOptionLayout->setVerticalSpacing(0);
    //systemOptionLayout->setHorizontalSpacing(0);
    for(int i = 0; i < systemOptionLayout->columnCount(); i++)
        systemOptionLayout->setColumnStretch(i, 1);
    for(int i = 0; i < systemOptionLayout->rowCount(); i++)
        systemOptionLayout->setRowStretch(i, 1);
    setLayout(systemOptionLayout);
    QObject::connect(comButton, &QPushButton::clicked, [](){qDebug() << "clLL";});
    QObject::connect(listen, &QPushButton::clicked, this, &SystemOption::newlisten);
    QObject::connect(linkStatus, static_cast<void(QComboBox::*)(int index)>(&QComboBox::currentIndexChanged), [=](int a){qDebug() << a << "current";});
    //test code, it will be deleted in released version
    QObject::connect(linkStatus, static_cast<void(QComboBox::*)(int index)>(&QComboBox::currentIndexChanged), [=](){emit currentsocketChanged(getCurrentSocketDescriptor());});
}

void SystemOption::newlisten()
{
    /*
     * when the "Listen" button is clicked, the slots is called;
     * close the current listen, and get the TextEdit(getPort) Int : port, listen the port;
    */
    if(server->isListening())
        server->close();
    port = getPort->text().toInt();
    server->listen(QHostAddress::Any, static_cast<quint16>(port));
    serverStatus->setText("Listening Port" + QString::number(port));
}

SystemOption::~SystemOption()
{

}

void SystemOption::comboBoxAddItem(int socketDescriptor)
{
    /*
     * when new socket connects to the server, combo box add new item by QVariant;
    */
    QVariant itemData = socketDescriptor;
    linkStatus->addItem(QString::number(socketDescriptor), itemData);
    ipLabel->setText(QString::number(server->getClientNum()));
}

void SystemOption::comboBoxDeleteItem(int socketDescritor)
{
    /*
     * when socket disconnect from the host, combo box delete the socket item by socket descriptor
    */
    int index = linkStatus->findText(QString::number(socketDescritor));
    linkStatus->removeItem(index);
    ipLabel->setText(QString::number(server->getClientNum()));
}

int SystemOption::getCurrentSocketDescriptor() const
{
    /*
     * combox get index of current socket
    */
    qDebug() << "this is get current socket calling";
    if(server->linkList.size() >= 1)
        return linkStatus->currentText().toInt();
    else
        return -1;
}

TcpServer* SystemOption::getServer()
{
    return server;
}
