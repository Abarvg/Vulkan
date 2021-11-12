#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CVulkanComputing _vkComp1;
    CMainWindow w;
    w.setGeometry(100,100,350,350);
    w.show();
    return a.exec();
}
