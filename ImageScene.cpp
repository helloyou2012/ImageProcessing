#include "ImageScene.h"

ImageScene::ImageScene(QObject *parent) :
    QGraphicsScene(parent)
{
}
void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    QGraphicsScene::mousePressEvent(mouseEvent);
}
void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
void ImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent){
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
