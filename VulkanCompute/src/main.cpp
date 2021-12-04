#include "CComputeApplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CComputeApplication app;

    try {
        app.run();
    }
    catch (const std::runtime_error& e) {
        printf("%s\n", e.what());
        return EXIT_FAILURE;
    }
    std::cout << "Hey!";
    a.exit();
    return EXIT_SUCCESS;
}
