#ifndef STATUSANALYSIS_H
#define STATUSANALYSIS_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>

class StatusAnalysis : public QWidget
{
    Q_OBJECT
public:
    explicit StatusAnalysis(QWidget *parent = nullptr);
    ~StatusAnalysis();
private:
    QTextEdit *statusAnalysisText;
    QPushButton *stopMeasure;
    QPushButton *queryHistoryData;
    QPushButton *quit;
    QGridLayout *statusAnalysisLayout;
signals:
    void callHistoricalData();
public slots:
};

#endif // STATUSANALYSIS_H
