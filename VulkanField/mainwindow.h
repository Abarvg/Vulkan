#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QVector>

class Painting : public QWidget
{
    Q_OBJECT
public:
    QTime  p_startingTime;
    int    p_height;
    int    p_width;

    QImage drawDots();

    Painting(QWidget *parent = 0);
    ~Painting();
protected:
    void paintEvent(QPaintEvent *);

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Painting m_field;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
