#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QVector>

class Painting : public QWidget
{
    Q_OBJECT
public:
    QTime timeStart;
    int height;
    int width;
    QVector<QRgb>* dotsArray = new QVector<QRgb>[width*height];
    Painting(QWidget *parent = 0);
    ~Painting();
protected:
    void paintEvent(QPaintEvent *);
    QImage drawDots(QVector<QRgb> &data);
    void changeDotsArray();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Painting field;
    MainWindow(QWidget *parent = nullptr);


    ~MainWindow();
};
#endif // MAINWINDOW_H
