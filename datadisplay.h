#ifndef DATADISPLAY_H
#define DATADISPLAY_H

#include <QWidget>
#include <Qwt/qwt_thermo.h>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QTcpSocket>

class DataDisplay : public QWidget
{
public:
    DataDisplay(QWidget *parent = nullptr);
    ~DataDisplay();
private:
    QwtThermo *thermoMetre;
    QLabel *thermoLabel;
    QLabel *thermoLabelNum;
    QLabel *nodeSelectionLabel;
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
    QLabel *driftAngelNum;
    QGridLayout *dataDisplayLayout;
    int nowNode;
    QVector<int> nodeList;
signals:
    void nodeChanged(int node);
public slots:
    void getData(int socketDescriptor, QString data);
private slots:
    void currentSocketChanged(QTcpSocket *currentSocket);
    void currentNodeChanged(int index);
};

#endif // DATADISPLAY_H
