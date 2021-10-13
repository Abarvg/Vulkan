#include "mainwindow.h"
#include <QPainter>
#include <QTime>
#include <QImage>
#include <QRgb>
#include <QColor>

Painting::Painting(QWidget *parent)
    : QWidget(parent),
      p_startingTime(QTime::currentTime()),
      p_height(350),
      p_width(350)
{
}


QImage Painting::drawDots()
{
    uchar* dotsArray = new uchar[p_width*p_height*4];

    for (int i = 0; i < p_height*p_width; i++)
    {
        dotsArray[i*4] = 200;
        dotsArray[i*4+1] = (p_startingTime.msecsTo(QTime::currentTime())/10)%255;
        dotsArray[i*4+2] = 200;
        dotsArray[i*4+3] = 255;
    }
    QImage image;
    image = QImage(dotsArray, p_width, p_height, p_width*4, QImage::Format_ARGB32);
    update();
    return image;
}

void Painting::paintEvent(QPaintEvent *)
{
    QImage dots;
    dots = drawDots();
    QRect borders(0,0,p_height,p_width);
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::green);
    painter.drawImage(borders,dots);
    painter.end();
}

Painting::~Painting()
{
}

