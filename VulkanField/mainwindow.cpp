#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      field(this)
{
    field.move(0,0);
    field.resize(350,350);
    field.setVisible(true);
}

MainWindow::~MainWindow()
{
}

