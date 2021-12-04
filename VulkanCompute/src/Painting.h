#ifndef PAINTING_H
#define PAINTING_H
#include <QMainWindow>
#include <QTime>
#include <vulkanComputing.h>

class CPainting : public QWidget
{
    Q_OBJECT
public:
    CPainting(QWidget *parent = 0);
    ~CPainting();

 protected:
    QTime    _timeStarting;
    unsigned _uHeight_px;
    unsigned _uWidth_px;
    unsigned char*   _pDotsArray;
    QImage   _image;


    void drawDots();
    void paintEvent(QPaintEvent *);

};

#endif // PAINTING_H
