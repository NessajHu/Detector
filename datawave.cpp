#include "datawave.h"
#include <QColor>
#include <Qwt/qwt_plot_magnifier.h>
#include <Qwt/qwt_plot_panner.h>
#include <Qwt/qwt_plot_item.h>
#include <Qwt/qwt_legend.h>
#ifdef QT_DEBUG
#include <QDebug>
#endif
#include "datahandle.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "mainwindow.h"
#include <QMessageBox>

const int DataWave::maxDisplayPoints = 2000;

DataWave::DataWave(QWidget *parent) :
    QWidget(parent),
    plot(new QwtPlot(this)),
    canvas(new QwtPlotCanvas()),
    accelerationXCurve(new QwtPlotCurve("accelerationX")),
    accelerationYCurve(new QwtPlotCurve("accelerationY")),
    accelerationZCurve(new QwtPlotCurve("accelerationZ")),
    gyroscopeXCurve(new QwtPlotCurve("gyroscopeX")),
    gyroscopeYCurve(new QwtPlotCurve("gyroscopeY")),
    gyroscopeZCurve(new QwtPlotCurve("gyroscopeZ")),
    rollAngelCurve(new QwtPlotCurve("rollAngel")),
    pitchAngelCurve(new QwtPlotCurve("pitchAngel")),
    driftAngelCurve(new QwtPlotCurve("driftAngel")),
    legend(new QwtLegend(this)),
    dataWaveLayout(new QGridLayout(this)),
    nowDisplayPoints(0),
    nowSocketDescriptor(0),
    nowNodeDescriptor(0x7FFFFFFF)
{
    //canvas->setPalette(Qt::white);
    dataWaveLayout->addWidget(plot, 0, 0, 1, 1);
    setLayout(dataWaveLayout);
    plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    plot->setCanvas(canvas);
    plot->setAxisTitle(QwtPlot::xBottom, "time(s)->");
    plot->setAxisTitle(QwtPlot::yLeft, "");
    plot->setAxisAutoScale(QwtPlot::xBottom, false);
    plot->setAxisAutoScale(QwtPlot::yLeft, false);
    plot->setAxisScale(QwtPlot::xBottom, 0, 5);
    plot->setAxisScale(QwtPlot::yLeft, 0, 100);
    //accelerationXPoint << QPoint(1, 1) << QPoint(2, 2);
    //accelerationYPoint << QPoint(5, 5) << QPoint(6, 6);
    accelerationXCurve->setSamples(accelerationXPoint);
    accelerationYCurve->setSamples(accelerationYPoint);
    accelerationXCurve->setPen(QColor(0, 0, 255), 2);
    accelerationXCurve->attach(plot);
    accelerationYCurve->setPen(QColor(0, 245, 255), 2);
    accelerationYCurve->attach(plot);
    accelerationZCurve->setPen(QColor(0, 255, 0), 2);
    accelerationZCurve->attach(plot);
    gyroscopeXCurve->setPen(QColor(255, 255, 0), 2);
    gyroscopeXCurve->attach(plot);
    gyroscopeYCurve->setPen(QColor(255, 106, 106), 2);
    gyroscopeYCurve->attach(plot);
    gyroscopeZCurve->setPen(QColor(255, 0, 0), 2);
    gyroscopeZCurve->attach(plot);
    rollAngelCurve->setPen(QColor(148, 0, 211), 2);
    rollAngelCurve->attach(plot);
    pitchAngelCurve->setPen(QColor(238, 118, 0), 2);
    pitchAngelCurve->attach(plot);
    driftAngelCurve->setPen(QColor(105, 105, 105), 2);
    driftAngelCurve->attach(plot);
    [[maybe_unused]] QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(plot->canvas());
    //magnifier (rooler zoom)
    [[maybe_unused]] QwtPlotPanner *panner = new QwtPlotPanner(plot->canvas());
    //panner (drag)
    legend->setDefaultItemMode(QwtLegendData::Checkable);
    //makes lefend button checkabke
    plot->insertLegend(legend, QwtPlot::RightLegend);
    plot->setFont(legendFont);
    //only legend font, not plot legend
    //connect(legend, &QwtLegend::checked, this, &DataWave::showItemChecked);
    //void(QwtLegend:: *temp)(const QVariant &, bool, int) = &QwtLegend::checked;
    //connect(legend, temp, this, &DataWave::showItemChecked);
    connect(legend, static_cast<void(QwtLegend::*)(const QVariant &, bool, int)>(&QwtLegend::checked), this, &DataWave::showItemChecked);
    //QObject::connect(legend, SIGNAL(checked(const QVariant &, bool, int)), this, SLOT(showItemChecked(const QVariant &, bool)));
    //QObject::connect(legend, static_cast<void (QwtLegend::*)(const QVariant &, bool, int)>(&QwtLegend::checked), this, &DataWave::showItemChecked);
    plot->replot();
    plot->setAutoReplot();
    /*for(int i = 0; i < plot->itemList().size(); i++)
    {
        QwtPlotItem *item = plot->itemList()[i]
    }*/
}

void DataWave::showItemChecked(const QVariant &itemInfo, bool on)
{
    QwtPlotItem *plotItem = plot->infoToItem(itemInfo);
    if(plotItem)
            plotItem->setVisible(on);
    plot->replot();
}

DataWave::~DataWave()
{
}

/**
 * @brief DataWave::getData
 * get Data from lower computer. Draw Curves. Insert to database
 * @param socketDescriptor
 * @param data
 */


void DataWave::getData(int socketDescriptor, QString data)
{
    DataHandle handler(data);
#ifdef QT_DEBUG
    qDebug() << "already recive";
#endif
    bool clearFlag = false;
    if(socketDescriptor != nowSocketDescriptor && nowSocketDescriptor != 0)
    {
        nowSocketDescriptor = socketDescriptor;
        clearFlag = true;
    }
    if(nowNodeDescriptor != static_cast<int>(handler.getData()[0]))
    {
        nowNodeDescriptor = static_cast<int>(handler.getData()[0]);
        clearFlag = true;
    }
    if(clearFlag)
    {
        nowDisplayPoints = 0;
        accelerationXPoint.clear();
        accelerationYPoint.clear();
        accelerationZPoint.clear();
        gyroscopeXPoint.clear();
        gyroscopeYPoint.clear();
        gyroscopeZPoint.clear();
        rollAngelPoint.clear();
        pitchAngelPoint.clear();
        driftAngelPoint.clear();
    }
    nowDisplayPoints += 1;
    if(nowDisplayPoints >= maxDisplayPoints)
    {
        accelerationXPoint.erase(accelerationXPoint.begin());
        accelerationYPoint.erase(accelerationYPoint.begin());
        accelerationZPoint.erase(accelerationZPoint.begin());
        gyroscopeXPoint.erase(gyroscopeXPoint.begin());
        gyroscopeYPoint.erase(gyroscopeYPoint.begin());
        gyroscopeZPoint.erase(gyroscopeZPoint.begin());
        rollAngelPoint.erase(rollAngelPoint.begin());
        pitchAngelPoint.erase(pitchAngelPoint.begin());
        driftAngelPoint.erase(driftAngelPoint.begin());
    }
    QSqlDatabase database = MainWindow::getDatabase();
    QSqlQuery insertQuery(database);
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    QString insertQueryString = QString("insert into log (time, node, accelerationX,  accelerationY, accelerationZ, temperature, gyroscopeX, gyroscopeY, gyroscopeZ, rollAngel, pitchAngel, driftAngel)"
                            "values('%1', %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12)")
            .arg(dateTime)
            .arg(nowNodeDescriptor)
            .arg(static_cast<int>(handler.getData()[1]))
            .arg(static_cast<int>(handler.getData()[2]))
            .arg(static_cast<int>(handler.getData()[3]))
            .arg(handler.getData()[4])
            .arg(static_cast<int>(handler.getData()[5]))
            .arg(static_cast<int>(handler.getData()[6]))
            .arg(static_cast<int>(handler.getData()[7]))
            .arg(handler.getData()[8])
            .arg(handler.getData()[9])
            .arg(handler.getData()[10]);
    if(!insertQuery.exec(insertQueryString))
        QMessageBox::critical(nullptr, QString::fromUtf8("Insert Failed"), insertQuery.lastError().text());
#ifdef QT_DEBUG
    else {
        qDebug() << "insert Success";
    }
#endif
    accelerationXPoint << QPointF(nowDisplayPoints, handler.getData()[1]);
    accelerationXCurve->setSamples(accelerationXPoint);
    accelerationYPoint << QPointF(nowDisplayPoints, handler.getData()[2]);
    accelerationYCurve->setSamples(accelerationXPoint);
    accelerationZPoint << QPointF(nowDisplayPoints, handler.getData()[3]);
    accelerationZCurve->setSamples(accelerationXPoint);
    gyroscopeXPoint << QPointF(nowDisplayPoints, handler.getData()[5]);
    gyroscopeXCurve->setSamples(accelerationXPoint);
    gyroscopeZPoint << QPointF(nowDisplayPoints, handler.getData()[6]);
    gyroscopeZCurve->setSamples(accelerationXPoint);
    gyroscopeYPoint << QPointF(nowDisplayPoints, handler.getData()[7]);
    gyroscopeYCurve->setSamples(accelerationXPoint);
    rollAngelPoint << QPointF(nowDisplayPoints, handler.getData()[8]);
    rollAngelCurve->setSamples(rollAngelPoint);
    pitchAngelPoint << QPointF(nowDisplayPoints, handler.getData()[9]);
    pitchAngelCurve->setSamples(pitchAngelPoint);
    driftAngelPoint << QPointF(nowDisplayPoints, handler.getData()[10]);
    driftAngelCurve->setSamples(driftAngelPoint);
    plot->setAxisScale(QwtPlot::xBottom, 0, nowDisplayPoints + 5);
    plot->replot();
}
