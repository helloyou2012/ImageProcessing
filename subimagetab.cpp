#include "subimagetab.h"

SubImageTab::SubImageTab(QVector<QRect> *rects,QImage *image,QWidget *parent) :
    QWidget(parent)
{
    subImageSize=100;
    rowSize=6;
    initWidget();
    addSubImageWidget(rects,image);
}
void SubImageTab::initWidget(){
    buttonGroup=new QButtonGroup(this);
    connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)),
                this, SLOT(buttonGroupClicked(QAbstractButton*)));

    QVBoxLayout *layout=new QVBoxLayout;
    imagesWidget=new QWidget();
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setAlignment(Qt::AlignHCenter);
    scrollArea->setWidget(imagesWidget);
    layout->addWidget(createToolBar());
    layout->addWidget(scrollArea);
    this->setLayout(layout);
}
QToolBar *SubImageTab::createToolBar(){
    QToolBar* toolbar=new QToolBar();
    QAction * deleteAction=new QAction(QIcon(":/menu_delete.png"),
                                       tr("Delete"), this);
    QAction * viewAction=new QAction(QIcon(":/menu_view.png"),
                                     tr("View"), this);
    QAction * analyseAction=new QAction(QIcon(":/menu_analyse.png"),
                                        tr("Analyse"), this);
    connect(deleteAction, SIGNAL(triggered()),this, SLOT(handleDelete()));
    connect(viewAction, SIGNAL(triggered()),this, SLOT(handleView()));
    connect(analyseAction, SIGNAL(triggered()),this, SLOT(handleAnalyse()));

    toolbar->addAction(deleteAction);
    toolbar->addAction(viewAction);
    toolbar->addAction(analyseAction);
    return toolbar;
}
void SubImageTab::handleDelete(){
    removeSelected();
}

void SubImageTab::handleView(){

}

void SubImageTab::handleAnalyse(){

}

void SubImageTab::buttonGroupClicked(QAbstractButton *button)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *myButton, buttons) {
        if (myButton != button)
            button->setChecked(false);
    }
}
void SubImageTab::addSubImageWidget(QVector<QRect> *rects,QImage *image){
    for (int i = 0; i < rects->size(); ++i) {
        QRect rect=rects->at(i);
        QImage *temp=new QImage(rect.size(),QImage::Format_RGB32);
        QPainter painter(temp);
        painter.drawImage(0,0,*image,rect.x(),rect.y(),rect.width(),rect.height());
        painter.end();
        SubImageWidget *widget=new SubImageWidget(temp);
        widget->setCheckable(true);
        widget->setFixedSize(subImageSize,subImageSize);
        buttonGroup->addButton(widget);
    }
    updateSubImage();

}

void SubImageTab::addSubImageWidget(QRect &rect,QImage *image){
    QImage *temp=new QImage(rect.size(),QImage::Format_RGB32);
    QPainter painter(temp);
    painter.drawImage(0,0,*image,rect.x(),rect.y(),rect.width(),rect.height());
    painter.end();
    SubImageWidget *widget=new SubImageWidget(temp);
    widget->setCheckable(true);
    widget->setFixedSize(subImageSize,subImageSize);
    buttonGroup->addButton(widget);
    updateSubImage();
}
void SubImageTab::updateSubImage(){
    QGridLayout *mainLayout = new QGridLayout;
    int i=0;
    foreach (QAbstractButton *widget, buttonGroup->buttons()) {
        mainLayout->addWidget(widget,i/rowSize, i%rowSize);
        i++;
    }
    mainLayout->setRowStretch(2, 10);
    mainLayout->setColumnStretch(2, 10);
    if(imagesWidget->layout()!=NULL)
        delete imagesWidget->layout();
    imagesWidget->setLayout(mainLayout);
    imagesWidget->adjustSize();
}

void SubImageTab::removeSelected(){
    QAbstractButton *button=NULL;
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *widget, buttons) {
        if(widget->isChecked())
            button=widget;
    }
    if(button!=NULL){
        buttonGroup->removeButton(button);
        delete button;
    }
    updateSubImage();
}
