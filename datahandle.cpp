#include "datahandle.h"
#include <QDebug>

const QRegExp DataHandle::dataRegExp = QRegExp(".*(-?\\d+).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{2}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*");

DataHandle::DataHandle(QString t) :
    data(11)
{
    if(dataRegExp.indexIn(t) != -1)
    {
        for(int i = 0; i < 11; i++)
            data[i] = dataRegExp.cap(i + 1).toDouble();
    }
}

DataHandle::~DataHandle()
{

}

QVector<double> DataHandle::getData()
{
    return data;
}

