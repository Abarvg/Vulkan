#include "Painting.h"
#include "const.h"
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QImage>
#include <iostream>
#include <QPixelFormat>
#include <vulkan/vulkan.h>
#include <unistd.h>

CPainting::CPainting(QWidget *parent)
    :QWidget(parent)
    ,_timeStarting(QTime::currentTime())
    ,_uHeight_px(WIDTH)
    ,_uWidth_px(HEIGHT)
{
    try {
        app.initVulkan();
    }
    catch (const std::runtime_error& e) {
        printf("%s\n", e.what());
    }
    _pDotsArray = new unsigned char[_uWidth_px*_uHeight_px*4];
    _image = QImage(_pDotsArray, _uWidth_px, _uHeight_px, _uWidth_px*4, QImage::Format_ARGB32);
    QTimer* pTimer = new QTimer(this);
    unsigned uUpdatePeriod_ms(1000);
    connect(pTimer,SIGNAL(timeout()),SLOT(update()));
    pTimer->start(uUpdatePeriod_ms);
    update();
}


void CPainting::drawDots()
{

    app.runCommandBuffer();
    app.saveRenderedImage(_pDotsArray);
//    int iTime_s;
//    int iTime2_s;
//    iTime_s = _timeStarting.secsTo(QTime::currentTime());
//    iTime2_s = _timeStarting.secsTo(QTime::currentTime().addMSecs(500));
//    for (unsigned i = 0; i < _uHeight_px*_uWidth_px; i++)
//    {
//        _pDotsArray[i*4] = 200;
//        _pDotsArray[i*4+1] = 50*(iTime_s)%255;
//        _pDotsArray[i*4+2] = 50*(iTime2_s)%255;
//        _pDotsArray[i*4+3] = 255;
//    }

}

void CPainting::paintEvent(QPaintEvent *)
{
    drawDots();
    QRect rectBorders(0,0,_uHeight_px,_uWidth_px);
    QPainter painter;
    painter.begin(this);
    painter.drawImage(rectBorders,_image);
    painter.end();
}

CPainting::~CPainting()
{
    app.cleanup();
    if (_pDotsArray)
        delete[] _pDotsArray;
}

