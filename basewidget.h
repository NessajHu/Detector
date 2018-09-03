#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include <QLabel>

class BaseWidget : public QWidget
{
public:
    BaseWidget(QWidget *parent = 0);
    QLabel *functionName = nullptr;
    ~BaseWidget();
};

#endif // BASEWIDGET_H
