#include "mainwindow.h"
#include "const.h"

CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_field(this)
{
    m_field.move(0,0);
    m_field.resize(WIDTH,HEIGHT);
    m_field.setVisible(true);
}

CMainWindow::~CMainWindow()
{
}

