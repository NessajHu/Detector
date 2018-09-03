#include "mainwindow.h"
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QDebug>

QString MainWindow::databaseConnection = "DetectorConnection";

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    systemOption(new SystemOption(this)),
    dataDisplay(new DataDisplay(this)),
    dataWave(new DataWave(this)),
    statusAnalysis(new StatusAnalysis(this)),
    mainWindowLayout(new QGridLayout(this)),
    historyData(new HistoricalData(nullptr))
{
    resize(800, 600);
    mainWindowFont.setFamily("Microsoft YaHei");
    mainWindowFont.setPixelSize(14);
    setFont(mainWindowFont);
    mainWindowLayout->addWidget(systemOption, 0, 0, 4, 4);
    mainWindowLayout->addWidget(dataDisplay, 0, 4, 4, 5);
    mainWindowLayout->addWidget(dataWave, 4, 0, 6, 6);
    mainWindowLayout->addWidget(statusAnalysis, 4, 6, 6, 3);
    for(int i = 0; i < mainWindowLayout->columnCount(); i++)
        mainWindowLayout->setColumnStretch(i, 1);
    for(int i = 0; i < mainWindowLayout->rowCount(); i++)
        mainWindowLayout->setRowStretch(i, 1);
    mainWindowLayout->setVerticalSpacing(0);
    mainWindowLayout->setHorizontalSpacing(0);
    mainWindowLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainWindowLayout);
    qDebug() << "shit";
    QObject::connect(statusAnalysis, &StatusAnalysis::callHistoricalData, [=](){historyData->show();});
    //QObject::connect(systemOption, &SystemOption::socketChanged, dataDisplay, &DataDisplay::currentSocketChanged);
    QObject::connect(systemOption->getServer(), &TcpServer::sendData, dataWave, &DataWave::getData);
    QObject::connect(systemOption->getServer(), &TcpServer::sendData, dataDisplay, &DataDisplay::getData);
    databaseInit();
}

void MainWindow::databaseInit()
{
    if(QSqlDatabase::contains(databaseConnection))
    {
        database = QSqlDatabase::database(databaseConnection);
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE", databaseConnection);
        database.setDatabaseName("detector.db");
    }
    if(!database.open())
    {
        QMessageBox openErrorMessageBox(QMessageBox::Warning,
                                        QString::fromUtf8("Error"),
                                        QString::fromUtf8("Open Database Error"));
        openErrorMessageBox.exec();
        QApplication::quit();
    }
    else
    {
        QSqlQuery tableExistQuery(database);
        if(tableExistQuery.exec("select count(*) from sqlite_master where type = 'table' and name = 'log'"))
        {
            while(tableExistQuery.next())
            {
                if(tableExistQuery.value(0).toInt() == 0)
                {
                    QSqlQuery createQuery(database);
                    if(!createQuery.exec("create table log(id integer primary key autoincrement, time datatime not null, node smallint not null, accelerationX smallint not null, accelerationY smallint not null, accerationZ smallint not null, temperature float not null, gyroscopeX smallint not null, gyroscopeY smallint not null, gyroscopeZ smallint not null, rollAngel float not null, pitchAngel float not null, drift Angel float not null)"))
                    {
                        QMessageBox createErrorMessageBox(QMessageBox::Warning,
                                                          QString::fromUtf8("Error"),
                                                          QString::fromUtf8("Create Database Error"));
                        createErrorMessageBox.exec();
                        QApplication::quit();
                    }
                    else
                        qDebug() << "success";
                }
            }
        }
        else
        {
            QMessageBox queryErrorMessageBox(QMessageBox::Warning,
                                              QString::fromUtf8("Error"),
                                              QString::fromUtf8("Query Error"));
            queryErrorMessageBox.exec();
            QApplication::quit();
        }
    }
}


MainWindow::~MainWindow()
{
    delete historyData;
}
