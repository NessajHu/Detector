#ifndef HISTORICALDATA_H
#define HISTORICALDATA_H

#include <QWidget>
#include <QTableView>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QSqlTableModel>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

class HistoricalData : public QWidget
{
    Q_OBJECT
public:
    HistoricalData(QWidget *parent = nullptr);
    ~HistoricalData();
    void show();
private:
    QSqlTableModel *tableModel;
    QTableView *dataTable;
    QComboBox *selectNode;
    QComboBox *sortOrder;
    QLabel *startingTimeLabel;
    QLabel *terminalTimeLabel;
    QDateTimeEdit *startingTime;
    QDateTimeEdit *terminalTime;
    QPushButton *selectButton;
    QGridLayout *layout;
signals:
private slots:
    void selected();
};

#endif // HISTORICALDATA_H
