#include <QApplication>
#include <login.h>
#include <menu.h>
#include <systemoption.h>
#include <systemoptioncontroller.h>
#include <datadisplay.h>
#include <measureddata.h>
#include <datawave.h>
#include <historicaldata.h>
#include <mainwindow.h>
#include <datahandle.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    //HistoricalData historicalData(&w, nullptr);
    //historicalData.hide();
    w.show();
    return a.exec();
}
