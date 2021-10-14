#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Painting.h"

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CPainting m_field;
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();
};
#endif // MAINWINDOW_H
