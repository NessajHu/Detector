#include "historicaldata.h"
#include "QStringList"
#include "QHeaderView"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QMessageBox>

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
    selectNode->addItem("");
    QObject::connect(selectButton, &QPushButton::clicked, this, &HistoricalData::selected);
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

void HistoricalData::show()
{
    //remove all items but the empty one
    for(int i = 0; i < selectNode->count() - 1; i++)
        selectNode->removeItem(1);
    QString nodeQueryString = "select node from log group by node";
    QSqlQuery nodeQuery(MainWindow::getDatabase());
    if(nodeQuery.exec(nodeQueryString))
    {
        while(nodeQuery.next())
        {
            QVariant node = nodeQuery.value(0).toInt();
            selectNode->addItem(QString::number(nodeQuery.value(0).toInt()), node);
        }
    }
#ifdef QT_DEBUG
    else
        qDebug() << __FILE__ << __func__ << __LINE__ << "error";
#endif
    tableModel->setFilter("");
    tableModel->select();
    QWidget::show();
}

/**
 * @brief HistoricalData::selected
 * Calling slot when the selectButton is clicked
 * select datetime and given node
 */
void HistoricalData::selected()
{
    if(terminalTime->dateTime() < startingTime->dateTime())
    {
#ifdef QT_DEBUG
        qDebug() << "Terminal time should later than starting time.";
#endif
        QMessageBox::critical(nullptr, QString::fromUtf8("Error"), QString::fromUtf8("Terminal time should later than starting time."));
        return;
    }
    QString terminalTimeString = terminalTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    QString startingTimeString = startingTime->dateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    QString filterString = "time >= '" + startingTimeString + "' and time <= '" + terminalTimeString + "'";
    if(selectNode->currentIndex() != 0)
        filterString += " and node = " + QString::number(selectNode->currentData().toInt());
#ifdef QT_DEBUG
    qDebug() << filterString;
#endif
    tableModel->setFilter(filterString);
    tableModel->select();
}
