#ifndef HISTORICALDATA_H
#define HISTORICALDATA_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QDateTimeEdit>

class HistoricalData : public QWidget
{
    Q_OBJECT
public:
    HistoricalData(QWidget *parent = nullptr);
    ~HistoricalData();
private:
    QTableWidget *dataTable;
    QComboBox *selectBox;
    QComboBox *sortOrder;
    QDateTimeEdit *startingTime;
    QDateTimeEdit *terminalTime;
signals:

public slots:
};

#endif // HISTORICALDATA_H
