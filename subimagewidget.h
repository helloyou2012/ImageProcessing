#ifndef SUBIMAGEWIDGET_H
#define SUBIMAGEWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QImage>
#include <QPainter>
#include <QtGui>

class SubImageWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit SubImageWidget(QImage *image=0,QWidget *parent = 0);
private:
    QImage *image;

protected:
    void paintEvent ( QPaintEvent * event );

signals:

public slots:

};

#endif // SUBIMAGEWIDGET_H
