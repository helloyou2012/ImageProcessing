#include "subimagewidget.h"

SubImageWidget::SubImageWidget(QImage *image,QWidget *parent) :
    QPushButton(parent)
{
    this->image=image;
}
void SubImageWidget::paintEvent(QPaintEvent *event)
{
    int w=this->width();
    int h=this->height();
    QPainter painter;
    painter.begin(this);
    if(this->isChecked()){
        QPen pen;
        pen.setWidth(2);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawRect(3,3,w-6,h-6);
    }
    QRect rect(8,8,w-16,h-16);
    painter.drawImage(rect,*this->image);
    painter.end();
}

