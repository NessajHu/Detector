#include "historicaldata.h"
#include "QStringList"
#include "QHeaderView"
#include "mainwindow.h"
#include <QSqlDatabase>

HistoricalData::HistoricalData(QWidget *parent) :
    QWidget(parent),
    tableModel(new QSqlTableModel(this, MainWindow::getDatabase())),
    dataTable(new QTableView(this)),
    selectNode(new QComboBox(this)),
    sortOrder(new QComboBox(this)),
    startingTime(new QDateTimeEdit(this)),
    terminalTime(new QDateTimeEdit(this)),
    selectButton(new QPushButton(this)),
    layout(new QGridLayout(this))
{
    setFixedSize(1200, 500);
    tableModel->setTable("log");
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableModel->select();
    dataTable->setModel(tableModel);
    layout->addWidget(dataTable, 0, 0, 8, 5);
    layout->addWidget(startingTime, 8, 0, 1, 1);
    layout->addWidget(terminalTime, 8, 1, 1, 1);
    layout->addWidget(selectNode, 8, 2, 1, 1);
    layout->addWidget(sortOrder, 8, 3, 1, 1);
    layout->addWidget(selectButton, 8, 4, 1, 1);
    /*dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
    startingTime->setCalendarPopup(true);*/
    //QObject::connect(w, &MainWindow::historicalDataShow, [=](){this->show();});
}

HistoricalData::~HistoricalData()
{

}
