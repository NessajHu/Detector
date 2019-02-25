#ifndef DATAHANDLE_H
#define DATAHANDLE_H

#include <QString>
#include <QChar>
#include <QRegExp>
#include <QVector>

class DataHandle
{
public:
    DataHandle(QString t);
    ~DataHandle();
    QVector<double> getData();
private:
    static const QRegExp dataRegExp;
    QVector<double> data;
    static const int dataSize;
};

#endif // DATAHANDLE_H
