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
    _pDotsArray = new uchar[_uWidth_px*_uHeight_px*4];
    _image = QImage(_pDotsArray, _uWidth_px, _uHeight_px, _uWidth_px*4, QImage::Format_ARGB32);
    QTimer* pTimer = new QTimer(this);
    unsigned uUpdatePeriod_ms(1000);
    connect(pTimer,SIGNAL(timeout()),SLOT(update()));
    pTimer->start(uUpdatePeriod_ms);
    update();
}


void CPainting::drawDots()
{

    int iTime_s;
    int iTime2_s;
    iTime_s = _timeStarting.secsTo(QTime::currentTime());
    iTime2_s = _timeStarting.secsTo(QTime::currentTime().addMSecs(500));
    for (unsigned i = 0; i < _uHeight_px*_uWidth_px; i++)
    {
        _pDotsArray[i*4] = 200;
        _pDotsArray[i*4+1] = 50*(iTime_s)%255;
        _pDotsArray[i*4+2] = 50*(iTime2_s)%255;
        _pDotsArray[i*4+3] = 255;
    }

}

void CPainting::paintEvent(QPaintEvent *)
{
    drawDots();
    QRect rectBorders(0,0,_uHeight_px,_uWidth_px);
    QPainter painter;
    painter.begin(this);
//    painter.setPen(Qt::NoPen);
    painter.drawImage(rectBorders,_image);
    painter.end();
}

CPainting::~CPainting()
{

    if (_pDotsArray)
        delete[] _pDotsArray;
}

