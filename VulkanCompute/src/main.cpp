#include "CComputeApplication.h"
#include <QApplication>
#include "mainwindow.h"
#include "const.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CComputeApplication app;
    CMainWindow w;
    w.setGeometry(100,100, WIDTH, HEIGHT);
    w.show();

    try {
        app.run();
    }
    catch (const std::runtime_error& e) {
        printf("%s\n", e.what());
        return EXIT_FAILURE;
    }
    std::cout << "Hey!";
    return a.exec();
}
