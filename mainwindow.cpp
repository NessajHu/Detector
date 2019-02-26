#include "mainwindow.h"
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>

QString MainWindow::databaseConnection = "DetectorConnection";

QSqlDatabase MainWindow::database = QSqlDatabase::database();

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    systemOption(new SystemOption(this)),
    dataDisplay(new DataDisplay(this)),
    dataWave(new DataWave(this)),
    statusAnalysis(new StatusAnalysis(this)),
    historyData(new HistoricalData(nullptr)),
    mainWindowLayout(new QGridLayout(this))
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
#ifdef QT_DEBUG
    qDebug() << "shit";
#endif
    QObject::connect(statusAnalysis, &StatusAnalysis::callHistoricalData, [=](){historyData->show();});
    //QObject::connect(systemOption, &SystemOption::socketChanged, dataDisplay, &DataDisplay::currentSocketChanged);
    QObject::connect(systemOption->getServer(), &TcpServer::sendData, dataWave, &DataWave::getData);
    QObject::connect(systemOption->getServer(), &TcpServer::sendData, dataDisplay, &DataDisplay::getData);
    QObject::connect(dataDisplay, &DataDisplay::nodeChanged, dataWave, &DataWave::nodeChanged);
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
        //if false, it means the query is failed.
        {
            while(tableExistQuery.next())
            {
                if(tableExistQuery.value(0).toInt() == 0)//value == 0 means there is no table called log.
                {
                    QSqlQuery createQuery(database);
                    if(!createQuery.exec("create table log(id integer primary key autoincrement, time datatime not null, node smallint not null, accelerationX smallint not null, accelerationY smallint not null, accelerationZ smallint not null, temperature float not null, gyroscopeX smallint not null, gyroscopeY smallint not null, gyroscopeZ smallint not null, rollAngel float not null, pitchAngel float not null, driftAngel float not null)"))
                    {
                        QMessageBox createErrorMessageBox(QMessageBox::Warning,
                                                          QString::fromUtf8("Error"),
                                                          createQuery.lastError().text());
                        createErrorMessageBox.exec();
                        QApplication::quit();
                    }
#ifdef QT_DEBUG
                    else
                        qDebug() << "Create success";
#endif
                }
            }
        }
        else
        {
            QMessageBox queryErrorMessageBox(QMessageBox::Warning,
                                             QString::fromUtf8("Error"),
                                             tableExistQuery.lastError().text());
            queryErrorMessageBox.exec();
            QApplication::quit();
        }
    }
}

QSqlDatabase& MainWindow::getDatabase()
{
    databaseInit();
    return database;
}

MainWindow::~MainWindow()
{
}
