#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui>
#include <QTabWidget>
#include <QRgb>
#include "ImageScene.h"
#include "OpencvFunction.h"
#include "ColorWeightDialog.h"
#include "ImageItem.h"
#include "subimagetab.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    ImageScene *scene;
    QGraphicsView *view;
    QAction *openAction;
    QAction *exitAction;
    QAction *saveAction;
    QAction *reloadAction;

    QAction *medianSmoothAction;//平滑
    QAction *gaussianSmoothAction;//平滑
    QAction *bilateralSmoothAction;//平滑

    QAction *binaryThresholdAction;//阈值化
    QAction *otsuThresholdAction;//阈值化
    QAction *adaptiveThresholdAction;//阈值化

    QAction *dilateAction;//膨胀
    QAction *erodeAction;//腐蚀
    QAction *openMorphologyAction;//开运算
    QAction *closeMorphologyAction;//闭运算
    QAction *tophatMorphologyAction;//顶帽运算
    QAction *bothatMorphologyAction;//黑帽运算

    QAction *histeqAction;//直方图均衡
    QAction *sobelEdgeAction;//Sobel变换
    QAction *cannyEdgeAction;//Canny变换
    QAction *laplaceEdgeAction;//拉普拉斯变换
    QAction *houghCircleEdgeAction;//霍夫圆变换

    QAction *binarySegmentAction;//二值化阈值分割
    QAction *otsuSegmentAction;//OTSU阈值分割
    QAction *adaptiveSegmentAction;//自适应阈值分割
    QAction *meanShiftSegmentAction;//均值漂移分割
    QAction *pyrSegmentAction;//金字塔分割

    QAction *colorWeightAction;//设置通道权值
    QAction *fillAreaAction;//填充区域
    QAction *fillColorAction;//颜色区域
    QAction *grayAction;//灰度变换

    QMenu *fileMenu;
    QMenu *settingMenu;
    QMenu *smoothMenu;//平滑处理
    QMenu *morphologyMenu;//形态学算法
    QMenu *thresholdMenu;//阈值化算法
    QMenu *transformMenu;//图像变换算法
    QMenu *segmentMenu;//分割算法
    IplImage *mainImage;
    IplImage *iplImage;
    QImage * qImage;
    ImageItem *imageItem;
    OpencvFunction *opencvFun;
    SubImageTab *subImageTab;
    QTabWidget *mainWidget;

private:
    void createActions();
    void createMenus();
    void copyImage();
    void iplImage2QImage();
    QImage *iplImage2QImage(IplImage *iplImg);

public slots:
  void slotOpenFile();
  void slotReloadFile();
  void slotExit();
  void slotMedianSmooth();
  void slotGaussianSmooth();
  void slotBilateralSmooth();
  void slotDilate();
  void slotErode();
  void slotOpenMorphology();
  void slotCloseMorphology();
  void slotTophatMorphology();
  void slotBothatMorphology();
  void slotBinaryThreshold();
  void slotOtsuThreshold();
  void slotAdaptiveThreshold();
  void slotHisteq();
  void slotSobelEdge();
  void slotCannyEdge();
  void slotLaplaceEdge();
  void slotHoughCircleEdge();
  void slotBinarySegment();
  void slotOtsuSegment();
  void slotAdaptiveSegment();
  void slotMeanShiftSegment();
  void slotPyrSegment();
  void slotColorWeight();
  void slotFillArea();
  void slotFillAreaPoint(int x,int y);
  void slotFillColor();
  void slotFillColorPoint(int x,int y);
  void slotConvertGray();
  void sceneRefresh();
  void slotProcessComplete(IplImage*ipldist);
  void slotDetectComplete(QVector<QRect>*rects);
};

#endif // MAINWINDOW_H
