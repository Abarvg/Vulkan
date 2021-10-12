#include "mainwindow.h"
#include <QPainter>
#include <QTime>
#include <QImage>

Painting::Painting(QWidget *parent)
    : QWidget(parent),
      timeStart(QTime::currentTime()),
      height(350),
      width(350)
{
}

void Painting::changeDotsArray()
{
    for (int i = 0; i < height*width; i++)
    {
        dotsArray[i][0] = 255;
        dotsArray[i][1] = 0;
        dotsArray[i][2] = 0;
        dotsArray[i][3] = 255;
    }

}

QImage Painting::drawDots(QVector<QRgb> &data)
{
    QImage image;
    image.fromData(data,"RGBA");//здесь должна быть функция, переводящая массив в картинку.
    //Я проверял: если картинка есть, она отрисовывается.
    return image;
}

void Painting::paintEvent(QPaintEvent *)
{
    QImage dots;
    dots = drawDots(*dotsArray);
    QRect borders(0,0,height,width);
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

