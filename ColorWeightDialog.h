#ifndef COLORWEIGHTDIALOG_H
#define COLORWEIGHTDIALOG_H

#include <QtGui>
#include <QDialog>

class ColorWeightDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ColorWeightDialog(double r=0,double g=0,double b=0,QWidget *parent = 0);
    double redWeight();
    double greenWeight();
    double blueWeight();

signals:

public slots:
    void slotValueChanged(int);
    void slotSetWeight();
private:
    QPushButton *okBtn;
    QSlider *redSlider;
    QSlider *greenSlider;
    QSlider *blueSlider;
    QLabel *redNumLabel;
    QLabel *greenNumLabel;
    QLabel *blueNumLabel;

    void refreshLabelValue();
};

#endif // COLORWEIGHTDIALOG_H
