#include "basewidget.h"
#include "QLabel"
#include "QFont"
/*
 * base class of all widgets
 * already modified:
 * size
 * system name and its font
*/
BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(600, 1000);
    QFont systemNameFont;
    systemNameFont.setFamily("Microsoft YaHei");
    systemNameFont.setPixelSize(27);
    systemNameFont.setBold(true);
    functionName = new QLabel(this);
    functionName->setGeometry(0, 0, 600, 100);
    functionName->setStyleSheet("Background-color:grey");
    functionName->setFont(systemNameFont);
    functionName->setAlignment(Qt::AlignCenter);
}

BaseWidget::~BaseWidget()
{

}
