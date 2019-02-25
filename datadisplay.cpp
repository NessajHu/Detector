#include "datadisplay.h"
#include <QDebug>
#include "datahandle.h"

DataDisplay::DataDisplay(QWidget *parent) :
    QWidget(parent),
    thermoMetre(new QwtThermo(this)),
    thermoLabel(new QLabel(this)),
    thermoLabelNum(new QLabel(this)),
    nodeSelectionLabel(new QLabel(this)),
    nodeSelection(new QComboBox(this)),
    accelerationX(new QLabel(this)),
    accelerationXNum(new QLabel(this)),
    accelerationY(new QLabel(this)),
    accelerationYNum(new QLabel(this)),
    accelerationZ(new QLabel(this)),
    accelerationZNum(new QLabel(this)),
    gyroscopeX(new QLabel(this)),
    gyroscopeXNum(new QLabel(this)),
    gyroscopeY(new QLabel(this)),
    gyroscopeYNum(new QLabel(this)),
    gyroscopeZ(new QLabel(this)),
    gyroscopeZNum(new QLabel(this)),
    rollAngel(new QLabel(this)),
    rollAngelNum(new QLabel(this)),
    pitchAngel(new QLabel(this)),
    pitchAngelNum(new QLabel(this)),
    driftAngel(new QLabel(this)),
    driftAngelNum(new QLabel(this)),
    dataDisplayLayout(new QGridLayout(this)),
    nodeList(0)
{
    thermoMetre->setOrientation(Qt::Horizontal);
    dataDisplayLayout->addWidget(thermoLabel, 0, 0, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(thermoLabelNum, 0, 1, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(thermoMetre, 0, 2, 1, 4, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(nodeSelectionLabel, 1, 0, 1, 2, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(nodeSelection, 1, 2, 1, 4, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(accelerationX, 2, 0, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(accelerationXNum, 2, 1, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(gyroscopeX, 2, 2, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(gyroscopeXNum, 2, 3, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(rollAngel, 2, 4, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(rollAngelNum, 2, 5, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(accelerationY, 3, 0, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(accelerationYNum, 3, 1, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(gyroscopeY, 3, 2, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(gyroscopeYNum, 3, 3, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(pitchAngel, 3, 4, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(pitchAngelNum, 3, 5, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(accelerationZ, 4, 0, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(accelerationZNum, 4, 1, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(gyroscopeZ, 4, 2, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(gyroscopeZNum, 4, 3, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(driftAngel, 4, 4, 1, 1, Qt::AlignVCenter);
    dataDisplayLayout->addWidget(driftAngelNum, 4, 5, 1, 1, Qt::AlignVCenter);
    //dataDisplayLayout->setVerticalSpacing(10);
    //dataDisplayLayout->setHorizontalSpacing(0);
    for(int i = 0; i < dataDisplayLayout->columnCount(); i++)
        dataDisplayLayout->setColumnStretch(i, 1);
    for(int i = 9; i < dataDisplayLayout->rowCount(); i++)
        dataDisplayLayout->setRowStretch(i, 1);
    setLayout(dataDisplayLayout);
    dataDisplayLayout->setAlignment(dataDisplayLayout, Qt::AlignVCenter);
    thermoLabel->setText("thermo");
    thermoMetre->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    nodeSelectionLabel->setText("Node Selection");
    nodeSelection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    nodeSelection->addItem("Point1");
    accelerationX->setText("aA");
    accelerationY->setText("aY");
    accelerationZ->setText("aZ");
    gyroscopeX->setText("gX");
    gyroscopeY->setText("gY");
    gyroscopeZ->setText("gZ");
    rollAngel->setText("rollAngel");
    pitchAngel->setText("pitchAngel");
    driftAngel->setText("driftAngel");
    QObject::connect(nodeSelection, static_cast<void(QComboBox::*)(int index)>(&QComboBox::currentIndexChanged), this, &DataDisplay::currentNodeChanged);
}

void DataDisplay::currentSocketChanged(QTcpSocket *currentSocket)
{
#ifdef QT_DEBUG
    if(currentSocket != nullptr)
        qDebug() << "this is datadisplay calling" << currentSocket->socketDescriptor();
    else
        qDebug() << "there is no socket linking to the server";
#endif
}

DataDisplay::~DataDisplay()
{

}

void DataDisplay::currentNodeChanged(int index)
{
    nowNode = nodeSelection->itemText(index).toInt();
    thermoLabelNum->setText("");
    thermoMetre->setValue(0);
    accelerationXNum->setText("");
    accelerationYNum->setText("");
    accelerationZNum->setText("");
    gyroscopeXNum->setText("");
    gyroscopeYNum->setText("");
    gyroscopeZNum->setText("");
    rollAngel->setText("");
    pitchAngel->setText("");
    driftAngel->setText("");
}

void DataDisplay::getData([[maybe_unused]] int socketDescriptor, QString data)
{
    DataHandle handler(data);
    int node = static_cast<int>(handler.getData()[0]);
    if(!nodeList.contains(node))
    {
        QVariant itemData = node;
        nodeSelection->addItem(QString::number(node), itemData);
    }
    thermoLabelNum->setText(QString::number(handler.getData()[4]));
    thermoMetre->setValue(handler.getData()[4]);
    accelerationXNum->setText(QString::number(handler.getData()[1]));
    accelerationYNum->setText(QString::number(handler.getData()[2]));
    accelerationZNum->setText(QString::number(handler.getData()[3]));
    gyroscopeXNum->setText(QString::number(handler.getData()[5]));
    gyroscopeYNum->setText(QString::number(handler.getData()[6]));
    gyroscopeZNum->setText(QString::number(handler.getData()[7]));
    rollAngelNum->setText(QString::number(handler.getData()[8]));
    pitchAngelNum->setText(QString::number(handler.getData()[9]));
    driftAngelNum->setText(QString::number(handler.getData()[10]));
}
