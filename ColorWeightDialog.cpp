#include "ColorWeightDialog.h"

ColorWeightDialog::ColorWeightDialog(double r,double g,double b,QWidget *parent) :
    QDialog(parent)
{
    QLabel *redLabel=new QLabel(trUtf8("Red通道"));
    QLabel *greenLabel=new QLabel(trUtf8("Green通道"));
    QLabel *blueLabel=new QLabel(trUtf8("Blue通道"));

    int rn=r*100,gn=g*100,bn=b*100;
    redSlider=new QSlider(Qt::Horizontal);
    redSlider->setValue(rn);
    redSlider->setMaximum(100);
    greenSlider=new QSlider(Qt::Horizontal);
    greenSlider->setValue(gn);
    greenSlider->setMaximum(100);
    blueSlider=new QSlider(Qt::Horizontal);
    blueSlider->setValue(bn);
    blueSlider->setMaximum(100);

    redNumLabel=new QLabel;
    greenNumLabel=new QLabel;
    blueNumLabel=new QLabel;

    okBtn=new QPushButton(trUtf8("设置"));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(redLabel, 0, 0);
    mainLayout->addWidget(redSlider, 0, 1, 1, 2);
    mainLayout->addWidget(redNumLabel, 0, 3,1,1,Qt::AlignCenter);
    mainLayout->addWidget(greenLabel, 1, 0);
    mainLayout->addWidget(greenSlider, 1, 1, 1, 2);
    mainLayout->addWidget(greenNumLabel, 1, 3,1,1,Qt::AlignCenter);
    mainLayout->addWidget(blueLabel, 2, 0);
    mainLayout->addWidget(blueSlider, 2, 1, 1, 2);
    mainLayout->addWidget(blueNumLabel, 2, 3,1,1,Qt::AlignCenter);

    QGroupBox *itemBox=new QGroupBox(trUtf8("设置权值"));
    itemBox->setLayout(mainLayout);
    itemBox->setStyleSheet("QGroupBox {\
                           border-width:1px;\
                           border-style:solid;\
                           border-color:lightGray;\
                           margin-top: 1ex;\
                           }\
                           QGroupBox::title {\
                           subcontrol-origin: margin;\
                           subcontrol-position: top left;\
                           left:20px; \
                           margin-left: 0px;\
                           padding:0 1px;\
                           }");
    QVBoxLayout *mainBox=new QVBoxLayout();
    mainBox->addWidget(itemBox);
    mainBox->addWidget(okBtn,0,Qt::AlignCenter);

    connect(redSlider,SIGNAL(valueChanged(int)),this,SLOT(slotValueChanged(int)));
    connect(greenSlider,SIGNAL(valueChanged(int)),this,SLOT(slotValueChanged(int)));
    connect(blueSlider,SIGNAL(valueChanged(int)),this,SLOT(slotValueChanged(int)));
    connect(okBtn,SIGNAL(clicked()),this,SLOT(slotSetWeight()));

    refreshLabelValue();
    setLayout(mainBox);
    setWindowTitle(trUtf8("设置通道权值"));
    resize(450,160);
}
void ColorWeightDialog::refreshLabelValue(){
    redNumLabel->setText(QString::number(redSlider->value())+"%");
    greenNumLabel->setText(QString::number(greenSlider->value())+"%");
    blueNumLabel->setText(QString::number(blueSlider->value())+"%");
}
void ColorWeightDialog::slotValueChanged(int){
    refreshLabelValue();
}
void ColorWeightDialog::slotSetWeight(){
    this->accept();
}
double ColorWeightDialog::redWeight(){
    return redSlider->value()/100.0;
}
double ColorWeightDialog::greenWeight(){
    return greenSlider->value()/100.0;
}
double ColorWeightDialog::blueWeight(){
    return blueSlider->value()/100.0;
}
