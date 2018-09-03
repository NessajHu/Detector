#include "menu.h"
#include <QPushButton>
#include <QFont>
#include <switchbutton.h>
/*
 * menu widget
 * sub widget:
 * system option
 * measured data
 * history(data)
 * Already modified:
 * function button and its font
 * window title
*/
Menu::Menu(QWidget *parent) : BaseWidget(parent)
{
    setWindowTitle("Menu");
    functionName->setText("OutDoors Advertisement Safety Detector");
    QFont buttonFont;
    buttonFont.setPixelSize(20);
    buttonFont.setFamily("Microsoft YaHei");
    QPushButton *systemOption = new QPushButton("System Option", this);
    systemOption->setFont(buttonFont);
    systemOption->setGeometry(200, 300, 200, 100);
    QPushButton *measuredData = new QPushButton("Measured Data", this);
    measuredData->setFont(buttonFont);
    measuredData->setGeometry(200, 500, 200, 100);
    QPushButton *history = new QPushButton("History", this);
    history->setFont(buttonFont);
    history->setGeometry(200, 700, 200, 100);
}

Menu::~Menu()
{

}
