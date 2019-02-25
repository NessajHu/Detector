#include "datahandle.h"

const QRegExp DataHandle::dataRegExp = QRegExp(".*(-?\\d+).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{2}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*(-?\\d+\\.\\d{7}).*");

const int DataHandle::dataSize = 11;

DataHandle::DataHandle(QString t) :
    data(dataSize)
{
    if(dataRegExp.indexIn(t) != -1)
    {
        for(int i = 0; i < dataSize; i++)
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

