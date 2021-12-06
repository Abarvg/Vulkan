#include "CComputeApplication.h"
#include <QApplication>
#include "mainwindow.h"
#include "const.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CMainWindow w;
    w.setGeometry(100,100, WIDTH, HEIGHT);
    w.show();
    std::cout << "Hey!";
    return a.exec();
}
