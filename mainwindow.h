#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "systemoption.h"
#include "datadisplay.h"
#include "datawave.h"
#include "statusanalysis.h"
#include <QFont>
#include <QGridLayout>
#include <QtSql/QSqlDatabase>
#include <QApplication>
#include "historicaldata.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:

private:
    SystemOption *systemOption;
    DataDisplay *dataDisplay;
    DataWave *dataWave;
    StatusAnalysis *statusAnalysis;
    HistoricalData *historyData;
    QFont mainWindowFont;
    QGridLayout *mainWindowLayout;
    static QString databaseConnection;
    QSqlDatabase database;
    void databaseInit();
};

#endif // MAINWINDOW_H
