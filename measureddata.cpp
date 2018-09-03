#include "measureddata.h"

MeasuredData::MeasuredData(QWidget *parent) :QWidget(parent)
{
    resize(500,500);
    thermoLabel = new QLabel(this);
    thermoLabelNum = new QLabel(this);
    hygroLabel = new QLabel(this);
    thermoLabel->setText("test");
    thermoLabelNum->setText("temp");
    hygroLabel->setText("test1");
    thermoLabel->setGeometry(0, 0, 100, 100);
    thermoLabelNum->setGeometry(100, 100, 100, 100);
    hygroLabel->setGeometry(200, 200, 100, 100);
}

MeasuredData::~MeasuredData()
{

}
