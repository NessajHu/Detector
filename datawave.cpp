#include "datawave.h"
#include <QColor>
#include <Qwt/qwt_plot_magnifier.h>
#include <Qwt/qwt_plot_panner.h>
#include <Qwt/qwt_plot_item.h>
#include <Qwt/qwt_legend.h>
#include <QDebug>
#include "datahandle.h"

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
    now(0),
    nowSocketDescriptor(0)
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



    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(plot->canvas());
    //magnifier (rooler zoom)
    QwtPlotPanner *panner = new QwtPlotPanner(plot->canvas());
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
    qDebug() << "test";
    QwtPlotItem *plotItem = plot->infoToItem(itemInfo);
    if(plotItem)
            plotItem->setVisible(on);
    plot->replot();
}

DataWave::~DataWave()
{

}

void DataWave::getData(int socketDescriptor, QString data)
{
    DataHandle handler(data);
    qDebug() << "already recive";
    if(socketDescriptor != nowSocketDescriptor && nowSocketDescriptor != 0)
    {
        now = 0;
        {
            QPolygonF temp;
            temp.swap(accelerationXPoint);
        }
        {
            QPolygonF temp;
            temp.swap(accelerationYPoint);
        }
        {
            QPolygonF temp;
            temp.swap(accelerationZPoint);
        }
        {
            QPolygonF temp;
            temp.swap(gyroscopeXPoint);
        }
        {
            QPolygonF temp;
            temp.swap(gyroscopeYPoint);
        }
        {
            QPolygonF temp;
            temp.swap(gyroscopeZPoint);
        }
        {
            QPolygonF temp;
            temp.swap(rollAngelPoint);
        }
        {
            QPolygonF temp;
            temp.swap(pitchAngelPoint);
        }
        {
            QPolygonF temp;
            temp.swap(driftAngelPoint);
        }
    }
    now += 1;
    accelerationXPoint << QPointF(now, handler.getData()[1]);
    accelerationXCurve->setSamples(accelerationXPoint);
    accelerationYPoint << QPointF(now, handler.getData()[2]);
    accelerationYCurve->setSamples(accelerationXPoint);
    accelerationZPoint << QPointF(now, handler.getData()[3]);
    accelerationZCurve->setSamples(accelerationXPoint);
    gyroscopeXPoint << QPointF(now, handler.getData()[5]);
    gyroscopeXCurve->setSamples(accelerationXPoint);
    gyroscopeZPoint << QPointF(now, handler.getData()[6]);
    gyroscopeZCurve->setSamples(accelerationXPoint);
    gyroscopeYPoint << QPointF(now, handler.getData()[7]);
    gyroscopeYCurve->setSamples(accelerationXPoint);
    rollAngelPoint << QPointF(now, handler.getData()[8]);
    rollAngelCurve->setSamples(rollAngelPoint);
    pitchAngelPoint << QPointF(now, handler.getData()[9]);
    pitchAngelCurve->setSamples(pitchAngelPoint);
    driftAngelPoint << QPointF(now, handler.getData()[10]);
    driftAngelCurve->setSamples(driftAngelPoint);
    plot->setAxisScale(QwtPlot::xBottom, 0, now + 5);
    plot->replot();
}
