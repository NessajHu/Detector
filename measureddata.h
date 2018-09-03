#ifndef MEASUREDDATA_H
#define MEASUREDDATA_H

#include <QWidget>
#include <QLabel>

class MeasuredData : public QWidget
{
public:
    MeasuredData(QWidget *parent);
    ~MeasuredData();
    /*QwtThermo *thermometre;
    QwtThermo *hygrometre;*/
    QLabel *thermoLabel;
    QLabel *thermoLabelNum;
    QLabel *hygroLabel;
    /*QLabel *hygroLabelNum;
    QComboBox *nodeSelection;
    QLabel *accelerationX;
    QLabel *accelerationXNum;
    QLabel *accelerationY;
    QLabel *accelerationYNum;
    QLabel *accelerationZ;
    QLabel *accelerationZNum;
    QLabel *gyroscopeX;
    QLabel *gyroscopeXNum;
    QLabel *gyroscopeY;
    QLabel *gyroscopeYNum;
    QLabel *gyroscopeZ;
    QLabel *gyroscopeZNum;
    QLabel *rollAngel;
    QLabel *rollAngelNum;
    QLabel *pitchAngel;
    QLabel *pitchAngelNum;
    QLabel *driftAngel;
    QLabel *driftAngelNum;*/
    //QGridLayout *dataDisplayLayout;
};

#endif // MEASUREDDATA_H
