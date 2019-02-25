#ifndef SYSTEMOPTION_H
#define SYSTEMOPTION_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "tcpserver.h"
#include <QGridLayout>
#include <QTcpSocket>

class SystemOption : public QWidget
{
    Q_OBJECT
public:
    SystemOption(QWidget *parent = nullptr);
    int getCurrentSocketDescriptor() const;
    TcpServer* getServer();
    ~SystemOption();
private:
    QLabel *comLabel;
    QComboBox *comComboBox;
    QLabel *baudRateLabel;
    QComboBox *baudRateComboBox;
    QPushButton *comButton;
    QLabel *comStatusLabel;
    QLabel *comStatus;
    QLabel *ipLabel;
    QLabel *portLabel;
    QLineEdit *getIp;
    QLineEdit *getPort;
    QPushButton *listen;
    QLabel *linkStatusLabel;
    QComboBox *linkStatus;
    QLabel *serverStatusLabel;
    QLabel *serverStatus;
    TcpServer *server;
    QGridLayout *systemOptionLayout;
    int port;
signals:
    void currentsocketChanged(int socketDescriptor);
public slots:
    void newlisten();
    void comboBoxAddItem(int socketDescriptor);
    void comboBoxDeleteItem(int socketDescritor);
};

#endif // SYSTEMOPTION_H
