#include "Painting.h"
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QImage>


CPainting::CPainting(QWidget *parent)
    : QWidget(parent),
      _timeStarting(QTime::currentTime()),
      _uHeight_px(350),
      _uWidth_px(350)
{
    QTimer* ptimer = new QTimer(this);
    connect(ptimer,SIGNAL(timeout()),SLOT(update()));
    ptimer->start(500);
    update();
}


QImage CPainting::drawDots()
{
    uchar* dotsArray = new uchar[_uWidth_px*_uHeight_px*4];
    int time;
    int time2;
    time = _timeStarting.secsTo(QTime::currentTime());
    time2 = _timeStarting.secsTo(QTime::currentTime().addMSecs(500));
    for (unsigned i = 0; i < _uHeight_px*_uWidth_px; i++)
    {
        dotsArray[i*4] = 200;
        dotsArray[i*4+1] = 50*(time)%255;
        dotsArray[i*4+2] = 50*(time2)%255;
        dotsArray[i*4+3] = 255;
    }
    QImage image;
    image = QImage(dotsArray, _uWidth_px, _uHeight_px, _uWidth_px*4, QImage::Format_ARGB32);
    return image;
}

void CPainting::paintEvent(QPaintEvent *)
{
    QImage dots;
    dots = drawDots();
    QRect borders(0,0,_uHeight_px,_uWidth_px);
    QPainter painter;
    painter.begin(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::green);
    painter.drawImage(borders,dots);
    painter.end();
}

CPainting::~CPainting()
{
}

