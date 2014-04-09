#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QtGui/QGraphicsPixmapItem>
#include <QtGui>

class ImageItem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ImageItem();
    void setSelectType(int type);
signals:
    void selectedFillAreaPoint(int x,int y);
    void selectedFillColorPoint(int x,int y);
public slots:
private:
    int selectType;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

};

#endif // IMAGEITEM_H
