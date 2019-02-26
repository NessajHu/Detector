#ifndef DATAWAVE_H
#define DATAWAVE_H

#include <QWidget>
#include <Qwt/qwt_plot.h>
#include <Qwt/qwt_plot_curve.h>
#include <Qwt/qwt_plot_canvas.h>
#include <Qwt/qwt_legend.h>
#include <QPolygonF>
#include <QFont>
#include <QGridLayout>
#include <QPointer>

class DataWave : public QWidget
{
    Q_OBJECT
public:
    explicit DataWave(QWidget *parent = nullptr);
    ~DataWave();
private:
    QwtPlot *plot;
    QPointer<QwtPlotCanvas> canvas;
    QwtPlotCurve *accelerationXCurve;
    QPolygonF accelerationXPoint;
    QwtPlotCurve *accelerationYCurve;
    QPolygonF accelerationYPoint;
    QwtPlotCurve *accelerationZCurve;
    QPolygonF accelerationZPoint;
    QwtPlotCurve *gyroscopeXCurve;
    QPolygonF gyroscopeXPoint;
    QwtPlotCurve *gyroscopeYCurve;
    QPolygonF gyroscopeYPoint;
    QwtPlotCurve *gyroscopeZCurve;
    QPolygonF gyroscopeZPoint;
    QwtPlotCurve *rollAngelCurve;
    QPolygonF rollAngelPoint;
    QwtPlotCurve *pitchAngelCurve;
    QPolygonF pitchAngelPoint;
    QwtPlotCurve *driftAngelCurve;
    QPolygonF driftAngelPoint;
    QwtLegend *legend;
    QFont legendFont;
    QGridLayout *dataWaveLayout;
    int nowDisplayPoints;
    int nowSocketDescriptor;//it may be deleted
    int nowNodeDescriptor;
    void clearCurves();
    static const int maxDisplayPoints;
signals:

public slots:
    void showItemChecked(const QVariant &itemInfo, bool on);
    void getData(int socketDescriptor, QString data);
    void nodeChanged(int newNode);
};

#endif // DATAWAVE_H
