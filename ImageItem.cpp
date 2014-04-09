#include "ImageItem.h"

ImageItem::ImageItem()
{
    selectType=0;
}

void ImageItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    QPointF p1=mouseEvent->pos();
    QPointF p2=this->offset();
    int px=p1.rx()-p2.rx();
    int py=p1.ry()-p2.ry();
    if(selectType==1){
        emit selectedFillAreaPoint(px,py);
    }else if(selectType==2){
        emit selectedFillColorPoint(px,py);
    }
    QGraphicsPixmapItem::mousePressEvent(mouseEvent);
}
void ImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if(selectType==0){
        QToolTip::hideText();
        QGraphicsPixmapItem::mouseMoveEvent(mouseEvent);
    }else if(selectType==1){
        QToolTip::showText(mouseEvent->screenPos(),trUtf8("选择区域填充种子点"));
    }else if(selectType==2){
        QToolTip::showText(mouseEvent->screenPos(),trUtf8("选择颜色填充种子点"));
    }
}
void ImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if(selectType==0)
        QGraphicsPixmapItem::mouseReleaseEvent(mouseEvent);
}
void ImageItem::setSelectType(int type){
    selectType=type;
}
