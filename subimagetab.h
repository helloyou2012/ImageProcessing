#ifndef SUBIMAGETAB_H
#define SUBIMAGETAB_H

#include <QButtonGroup>
#include <QtGui>
#include "subimagewidget.h"

class SubImageTab : public QWidget
{
    Q_OBJECT
public:
    explicit SubImageTab(QVector<QRect> *rects,QImage *image,QWidget *parent = 0);

    void addSubImageWidget(QRect &rect,QImage *image);
    void removeSelected();
    void updateSubImage();
    void initWidget();
    void addSubImageWidget(QVector<QRect> *rects,QImage *image);
    QToolBar *createToolBar();
private:
    QButtonGroup *buttonGroup;
    QWidget *imagesWidget;
    int subImageSize;
    int rowSize;

signals:

private slots:
    void buttonGroupClicked(QAbstractButton *button);
    void handleDelete();
    void handleView();
    void handleAnalyse();
};

#endif // SUBIMAGETAB_H
