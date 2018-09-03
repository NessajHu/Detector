#include "historicaldata.h"
#include "QStringList"
#include "QHeaderView"

HistoricalData::HistoricalData(QWidget *parent) :
    QWidget(parent),
    dataTable(new QTableWidget(this)),
    selectBox(new QComboBox(this)),
    sortOrder(new QComboBox(this)),
    startingTime(new QDateTimeEdit(this)),
    terminalTime(new QDateTimeEdit(this))
{
    setFixedSize(500, 500);
    dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dataTable->verticalHeader()->setVisible(false);
    dataTable->setColumnCount(5);
    dataTable->setRowCount(6);
    QStringList dataTableHeaders;
    dataTableHeaders << "Date" << "Time" << "Roll" << "Pitch" << "Drift";
    dataTable->setHorizontalHeaderLabels(dataTableHeaders);
    //dataTable->hide();
    selectBox->addItem("Thermo");
    selectBox->addItem("Acceleration");
    selectBox->addItem("Gyro");
    selectBox->addItem("Angel");
    selectBox->hide();
    sortOrder->addItem("Descending Order");
    sortOrder->addItem("ascending Order");
    selectBox->hide();
    terminalTime->hide();
    startingTime->hide();
    startingTime->setCalendarPopup(true);
    //QObject::connect(w, &MainWindow::historicalDataShow, [=](){this->show();});
}

HistoricalData::~HistoricalData()
{

}
