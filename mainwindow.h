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
    static QSqlDatabase& getDatabase();
    ~MainWindow();
public slots:

private:
    SystemOption *systemOption;
    DataDisplay *dataDisplay;
    DataWave *dataWave;
    StatusAnalysis *statusAnalysis;
    QPointer<HistoricalData> historyData;
    QFont mainWindowFont;
    QGridLayout *mainWindowLayout;
    static QString databaseConnection;
    static QSqlDatabase database;
    static void databaseInit();
};

#endif // MAINWINDOW_H
