#include "statusanalysis.h"

StatusAnalysis::StatusAnalysis(QWidget *parent) :
    QWidget(parent),
    statusAnalysisText(new QTextEdit(this)),
    stopMeasure(new QPushButton(this)),
    queryHistoryData(new QPushButton(this)),
    quit(new QPushButton(this)),
    statusAnalysisLayout(new QGridLayout(this))
{
    statusAnalysisLayout->addWidget(statusAnalysisText, 0, 0, 1, 3);
    statusAnalysisLayout->addWidget(stopMeasure, 1, 0, 1, 1);
    statusAnalysisLayout->addWidget(queryHistoryData, 1, 1, 1, 1);
    statusAnalysisLayout->addWidget(quit, 1, 2, 1, 1);
    setLayout(statusAnalysisLayout);
    stopMeasure->setText("Stop");
    queryHistoryData->setText("History");
    quit->setText("Quit");
    QObject::connect(queryHistoryData, &QPushButton::clicked, [=](){emit callHistoricalData();});
}

StatusAnalysis::~StatusAnalysis()
{

}
