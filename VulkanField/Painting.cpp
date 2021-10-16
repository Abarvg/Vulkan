#include "Painting.h"
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QImage>
#include <iostream>


CPainting::CPainting(QWidget *parent)
    : QWidget(parent),
      _timeStarting(QTime::currentTime()),
      _uHeight_px(350),
      _uWidth_px(350)
{
    _dotsArray = new uchar[_uWidth_px*_uHeight_px*4];
    QTimer* updateFreq = new QTimer(this);
    connect(updateFreq,SIGNAL(timeout()),SLOT(update()));
    updateFreq->start(1000);
    update();
}


void CPainting::drawDots()
{

    int time;
    int time2;
    time = _timeStarting.secsTo(QTime::currentTime());
    time2 = _timeStarting.secsTo(QTime::currentTime().addMSecs(500));
    for (unsigned i = 0; i < _uHeight_px*_uWidth_px; i++)
    {
        _dotsArray[i*4] = 200;
        _dotsArray[i*4+1] = 50*(time)%255;
        _dotsArray[i*4+2] = 50*(time2)%255;
        _dotsArray[i*4+3] = 255;
    }
    _image = QImage(_dotsArray, _uWidth_px, _uHeight_px, _uWidth_px*4, QImage::Format_ARGB32);
}

void CPainting::paintEvent(QPaintEvent *)
{
    drawDots();
    QRect borders(0,0,_uHeight_px,_uWidth_px);
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::green);
    painter.drawImage(borders,_image);
    painter.end();
}

CPainting::~CPainting()
{
    delete(_dotsArray);
}

