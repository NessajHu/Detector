#include "datadisplay.h"
#include <QDebug>
#include "datahandle.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "mainwindow.h"
#include <QMessageBox>

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
    emit nodeChanged(nowNode);
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
#ifdef QT_DEBUG
    qDebug() << "node not in the list";
    for(auto i : nodeList)
        qDebug() << i << "list";
#endif
        nodeList.push_back(node);
        QVariant itemData = node;
        nodeSelection->addItem(QString::number(node), itemData);
    }
    QSqlDatabase database = MainWindow::getDatabase();
    QSqlQuery insertQuery(database);
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    QString insertQueryString = QString("insert into log (time, node, accelerationX,  accelerationY, accelerationZ, temperature, gyroscopeX, gyroscopeY, gyroscopeZ, rollAngel, pitchAngel, driftAngel)"
                            "values('%1', %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12)")
            .arg(dateTime)
            .arg(node)
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

void DataDisplay::clear()
{
    int count = nodeSelection->count();
    for(int i = 0; i < count; i++)
        nodeSelection->removeItem(0);
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
