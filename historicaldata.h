#ifndef HISTORICALDATA_H
#define HISTORICALDATA_H

#include <QWidget>
#include <QTableView>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QSqlTableModel>
#include <QGridLayout>
#include <QPushButton>

class HistoricalData : public QWidget
{
    Q_OBJECT
public:
    HistoricalData(QWidget *parent = nullptr);
    ~HistoricalData();
private:
    QSqlTableModel *tableModel;
    QTableView *dataTable;
    QComboBox *selectNode;
    QComboBox *sortOrder;
    QDateTimeEdit *startingTime;
    QDateTimeEdit *terminalTime;
    QPushButton *selectButton;
    QGridLayout *layout;
signals:

public slots:
};

#endif // HISTORICALDATA_H
