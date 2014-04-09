#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();
    mainImage=0;
    iplImage=0;
    qImage=0;
    opencvFun=new OpencvFunction();
    connect(opencvFun,SIGNAL(processComplete(IplImage*)),this,SLOT(slotProcessComplete(IplImage*)));
    connect(opencvFun,SIGNAL(detectComplete(QVector<QRect>*)),this,SLOT(slotDetectComplete(QVector<QRect>*)));
    //center
    mainWidget=new QTabWidget();
    //
    imageItem=new ImageItem;
    imageItem->setCursor(Qt::OpenHandCursor);
    imageItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    imageItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    connect(imageItem,SIGNAL(selectedFillAreaPoint(int,int)),this,SLOT(slotFillAreaPoint(int,int)));
    connect(imageItem,SIGNAL(selectedFillColorPoint(int,int)),this,SLOT(slotFillColorPoint(int,int)));
    scene = new ImageScene(this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    scene->addItem(imageItem);
    view = new QGraphicsView(scene);
    mainWidget->addTab(view,trUtf8("显示处理图像"));
    setCentralWidget(mainWidget);
    statusBar()->showMessage(trUtf8("程序已启动！"));
}

MainWindow::~MainWindow()
{

}
void MainWindow::createActions()
{
    openAction = new QAction(trUtf8("打开"), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(trUtf8("打开图像文件"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(slotOpenFile()));

    reloadAction = new QAction(trUtf8("重新载入"), this);
    reloadAction->setShortcuts(QKeySequence::New);
    reloadAction->setStatusTip(trUtf8("重新载入图像文件"));
    connect(reloadAction, SIGNAL(triggered()), this, SLOT(slotReloadFile()));

    exitAction = new QAction(trUtf8("退出"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(trUtf8("退出应用程序"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(slotExit()));

    saveAction = new QAction(trUtf8("保存"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(trUtf8("保存图像文件"));

    medianSmoothAction = new QAction(trUtf8("中值平滑"), this);
    medianSmoothAction->setStatusTip(trUtf8("对当前图像进行中值平滑处理"));
    connect(medianSmoothAction,SIGNAL(triggered()),this,SLOT(slotMedianSmooth()));

    gaussianSmoothAction = new QAction(trUtf8("高斯平滑"), this);
    gaussianSmoothAction->setStatusTip(trUtf8("对当前图像进行高斯平滑处理"));
    connect(gaussianSmoothAction,SIGNAL(triggered()),this,SLOT(slotGaussianSmooth()));

    bilateralSmoothAction = new QAction(trUtf8("双向平滑"), this);
    bilateralSmoothAction->setStatusTip(trUtf8("对当前图像进行双向平滑处理"));
    connect(bilateralSmoothAction,SIGNAL(triggered()),this,SLOT(slotBilateralSmooth()));

    binaryThresholdAction= new QAction(trUtf8("二值阈值化"), this);
    binaryThresholdAction->setStatusTip(trUtf8("对当前图像进行二值阈值化处理"));
    connect(binaryThresholdAction,SIGNAL(triggered()),this,SLOT(slotBinaryThreshold()));

    otsuThresholdAction= new QAction(trUtf8("OTSU阈值化"), this);
    otsuThresholdAction->setStatusTip(trUtf8("对当前图像进行OSTU阈值化处理"));
    connect(otsuThresholdAction,SIGNAL(triggered()),this,SLOT(slotOtsuThreshold()));

    adaptiveThresholdAction= new QAction(trUtf8("自适应阈值化"), this);
    adaptiveThresholdAction->setStatusTip(trUtf8("对当前图像进行自适应阈值化处理"));
    connect(adaptiveThresholdAction,SIGNAL(triggered()),this,SLOT(slotAdaptiveThreshold()));

    histeqAction= new QAction(trUtf8("直方图均衡化"), this);
    histeqAction->setStatusTip(trUtf8("对当前图像进行直方图均衡化处理"));
    connect(histeqAction,SIGNAL(triggered()),this,SLOT(slotHisteq()));

    sobelEdgeAction= new QAction(trUtf8("Sobel变换"), this);
    sobelEdgeAction->setStatusTip(trUtf8("对当前图像进行Sobel变换处理"));
    connect(sobelEdgeAction,SIGNAL(triggered()),this,SLOT(slotSobelEdge()));

    cannyEdgeAction= new QAction(trUtf8("Canny变换"), this);
    cannyEdgeAction->setStatusTip(trUtf8("对当前图像进行Canny变换处理"));
    connect(cannyEdgeAction,SIGNAL(triggered()),this,SLOT(slotCannyEdge()));

    laplaceEdgeAction= new QAction(trUtf8("拉普拉斯变换"), this);
    laplaceEdgeAction->setStatusTip(trUtf8("对当前图像进行拉普拉斯变换处理"));
    connect(laplaceEdgeAction,SIGNAL(triggered()),this,SLOT(slotLaplaceEdge()));

    houghCircleEdgeAction= new QAction(trUtf8("霍夫圆变换"), this);
    houghCircleEdgeAction->setStatusTip(trUtf8("对当前图像进行霍夫圆变换处理"));
    connect(houghCircleEdgeAction,SIGNAL(triggered()),this,SLOT(slotHoughCircleEdge()));

    dilateAction = new QAction(trUtf8("膨胀处理"), this);
    dilateAction->setStatusTip(trUtf8("对当前图像进行膨胀处理"));
    connect(dilateAction,SIGNAL(triggered()),this,SLOT(slotDilate()));

    erodeAction = new QAction(trUtf8("腐蚀处理"), this);
    erodeAction->setStatusTip(trUtf8("对当前图像进行腐蚀处理"));
    connect(erodeAction,SIGNAL(triggered()),this,SLOT(slotErode()));

    openMorphologyAction=new QAction(trUtf8("开运算"), this);
    openMorphologyAction->setStatusTip(trUtf8("对当前图像进行开运算处理"));
    connect(openMorphologyAction,SIGNAL(triggered()),this,SLOT(slotOpenMorphology()));

    closeMorphologyAction=new QAction(trUtf8("闭运算"), this);
    closeMorphologyAction->setStatusTip(trUtf8("对当前图像进行闭运算处理"));
    connect(closeMorphologyAction,SIGNAL(triggered()),this,SLOT(slotCloseMorphology()));

    tophatMorphologyAction=new QAction(trUtf8("顶帽运算"), this);
    tophatMorphologyAction->setStatusTip(trUtf8("对当前图像进行顶帽运算处理"));
    connect(tophatMorphologyAction,SIGNAL(triggered()),this,SLOT(slotTophatMorphology()));

    bothatMorphologyAction=new QAction(trUtf8("黑帽运算"), this);
    bothatMorphologyAction->setStatusTip(trUtf8("对当前图像进行黑帽运算处理"));
    connect(bothatMorphologyAction,SIGNAL(triggered()),this,SLOT(slotBothatMorphology()));

    binarySegmentAction=new QAction(trUtf8("二值化阈值分割"), this);
    binarySegmentAction->setStatusTip(trUtf8("对当前图像进行二值化阈值分割处理"));
    connect(binarySegmentAction,SIGNAL(triggered()),this,SLOT(slotBinarySegment()));

    otsuSegmentAction=new QAction(trUtf8("OTSU阈值分割"), this);
    otsuSegmentAction->setStatusTip(trUtf8("对当前图像进行OTSU阈值分割处理"));
    connect(otsuSegmentAction,SIGNAL(triggered()),this,SLOT(slotOtsuSegment()));

    adaptiveSegmentAction=new QAction(trUtf8("自适应阈值分割"), this);
    adaptiveSegmentAction->setStatusTip(trUtf8("对当前图像进行自适应阈值分割处理"));
    connect(adaptiveSegmentAction,SIGNAL(triggered()),this,SLOT(slotAdaptiveSegment()));

    meanShiftSegmentAction=new QAction(trUtf8("均值漂移分割"), this);
    meanShiftSegmentAction->setStatusTip(trUtf8("对当前图像进行均值漂移分割处理"));
    connect(meanShiftSegmentAction,SIGNAL(triggered()),this,SLOT(slotMeanShiftSegment()));

    pyrSegmentAction=new QAction(trUtf8("金字塔分割"), this);
    pyrSegmentAction->setStatusTip(trUtf8("对当前图像进行金字塔分割处理"));
    connect(pyrSegmentAction,SIGNAL(triggered()),this,SLOT(slotPyrSegment()));

    colorWeightAction=new QAction(trUtf8("设置通道权值"), this);
    colorWeightAction->setStatusTip(trUtf8("设置通道权值用于RGB转灰度图像"));
    connect(colorWeightAction,SIGNAL(triggered()),this,SLOT(slotColorWeight()));

    fillAreaAction=new QAction(trUtf8("区域填充"), this);
    fillAreaAction->setStatusTip(trUtf8("使用漫水填充方法进行区域填充"));
    connect(fillAreaAction,SIGNAL(triggered()),this,SLOT(slotFillArea()));
    fillColorAction=new QAction(trUtf8("颜色填充"), this);
    fillColorAction->setStatusTip(trUtf8("使用颜色填充方法进行区域填充"));
    connect(fillColorAction,SIGNAL(triggered()),this,SLOT(slotFillColor()));

    grayAction=new QAction(trUtf8("灰度变换"), this);
    grayAction->setStatusTip(trUtf8("对当前图像进行灰度变换处理"));
    connect(grayAction,SIGNAL(triggered()),this,SLOT(slotConvertGray()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(trUtf8("文件"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(reloadAction);
    fileMenu->addAction(exitAction);

    settingMenu = menuBar()->addMenu(trUtf8("设置"));
    settingMenu->addAction(colorWeightAction);
    settingMenu->addAction(fillAreaAction);
    settingMenu->addAction(fillColorAction);
    settingMenu->addAction(grayAction);

    smoothMenu=menuBar()->addMenu(trUtf8("平滑处理"));
    smoothMenu->addAction(medianSmoothAction);
    smoothMenu->addAction(gaussianSmoothAction);
    smoothMenu->addAction(bilateralSmoothAction);

    thresholdMenu=menuBar()->addMenu(trUtf8("阈值化"));
    thresholdMenu->addAction(binaryThresholdAction);
    thresholdMenu->addAction(otsuThresholdAction);
    thresholdMenu->addAction(adaptiveThresholdAction);

    morphologyMenu = menuBar()->addMenu(trUtf8("形态学操作"));
    morphologyMenu->addAction(dilateAction);
    morphologyMenu->addAction(erodeAction);
    morphologyMenu->addAction(openMorphologyAction);
    morphologyMenu->addAction(closeMorphologyAction);
    morphologyMenu->addAction(tophatMorphologyAction);
    morphologyMenu->addAction(bothatMorphologyAction);

    transformMenu = menuBar()->addMenu(trUtf8("图像变换"));
    transformMenu->addAction(histeqAction);
    transformMenu->addAction(sobelEdgeAction);
    transformMenu->addAction(cannyEdgeAction);
    transformMenu->addAction(laplaceEdgeAction);
    transformMenu->addAction(houghCircleEdgeAction);

    segmentMenu = menuBar()->addMenu(trUtf8("分割操作"));
    segmentMenu->addAction(binarySegmentAction);
    segmentMenu->addAction(otsuSegmentAction);
    segmentMenu->addAction(adaptiveSegmentAction);
    segmentMenu->addSeparator();
    segmentMenu->addAction(meanShiftSegmentAction);
    segmentMenu->addAction(pyrSegmentAction);
}

void MainWindow::slotProcessComplete(IplImage*ipldist){
    if(ipldist==iplImage){
        delete qImage;
        iplImage2QImage();
        sceneRefresh();
        return;
    }
    if(iplImage!=0){
        cvReleaseImage(&iplImage);
        delete qImage;
    }
    iplImage = cvCreateImage(cvSize(ipldist->width,ipldist->height),8,ipldist->nChannels);
    cvScale(ipldist,iplImage);
    iplImage2QImage();
    sceneRefresh();
}
void MainWindow::slotDetectComplete(QVector<QRect> *rects){
    if(mainImage!=0){
        IplImage *iplImg= cvCreateImage(cvGetSize(mainImage),mainImage->depth,mainImage->nChannels);
        if (mainImage->origin == IPL_ORIGIN_TL){
            cvCopy(mainImage,iplImg,0);
        }else{
            cvFlip(mainImage,iplImg,0);
        }
        QImage *qImg=iplImage2QImage(iplImg);
        if(iplImg!=0)
            cvReleaseImage(&iplImg);
        subImageTab=new SubImageTab(rects,qImg);
        delete qImg;
        mainWidget->addTab(subImageTab,trUtf8("分割后图像"));
    }
}

void MainWindow::iplImage2QImage(){
    qImage=iplImage2QImage(iplImage);
}
QImage * MainWindow::iplImage2QImage(IplImage *iplImg){
    QImage *qImg=new QImage(iplImg->width,iplImg->height,QImage::Format_RGB32);
    for(int i=0;i<iplImg->height;i++){
        for(int j=0;j<iplImg->width;j++){
            int r=0,g=0,b=0;
            if(iplImg->nChannels==3){
                b=(int)CV_IMAGE_ELEM(iplImg,uchar,i,j*3+0);
                g=(int)CV_IMAGE_ELEM(iplImg,uchar,i,j*3+1);
                r=(int)CV_IMAGE_ELEM(iplImg,uchar,i,j*3+2);

            }else if(iplImg->nChannels==1){
                b=(int)CV_IMAGE_ELEM(iplImg,uchar,i,j);
                g=b;
                r=b;
            }
            qImg->setPixel(j,i,qRgb(r,g,b));
        }
    }
    return qImg;
}

void MainWindow::slotMedianSmooth(){
    if(iplImage!=0){
        opencvFun->medianSmooth(iplImage);
    }
}
void MainWindow::slotGaussianSmooth(){
    if(iplImage!=0){
        opencvFun->gaussianSmooth(iplImage);
    }
}
void MainWindow::slotBilateralSmooth(){
    if(iplImage!=0){
        opencvFun->bilateralSmooth(iplImage);
    }
}
void MainWindow::slotDilate(){
    if(iplImage!=0){
        opencvFun->dilate(iplImage);
    }
}
void MainWindow::slotErode(){
    if(iplImage!=0){
        opencvFun->erode(iplImage);
    }
}
void MainWindow::slotOpenMorphology(){
    if(iplImage!=0){
        opencvFun->openingMorphology(iplImage);
    }
}
void MainWindow::slotCloseMorphology(){
    if(iplImage!=0){
        opencvFun->closingMorphology(iplImage);
    }
}
void MainWindow::slotTophatMorphology(){
    if(iplImage!=0){
        opencvFun->tophatMorphology(iplImage);
    }
}
void MainWindow::slotBothatMorphology(){
    if(iplImage!=0){
        opencvFun->bothatMorphology(iplImage);
    }
}

void MainWindow::slotBinaryThreshold(){
    if(iplImage!=0){
        opencvFun->binaryThreshold(iplImage);
    }
}

void MainWindow::slotOtsuThreshold(){
    if(iplImage!=0){
        opencvFun->otsuThreshold(iplImage);
    }
}
void MainWindow::slotAdaptiveThreshold(){
    if(iplImage!=0){
        opencvFun->adaptiveThreshold(iplImage);
    }
}

void MainWindow::slotHisteq(){
    if(iplImage!=0){
        opencvFun->histequal(iplImage);
    }
}
void MainWindow::slotSobelEdge(){
    if(iplImage!=0){
        opencvFun->sobelEdge(iplImage);
    }
}

void MainWindow::slotCannyEdge(){
    if(iplImage!=0){
        opencvFun->cannyEdge(iplImage);
    }
}

void MainWindow::slotLaplaceEdge(){
    if(iplImage!=0){
        opencvFun->laplaceEdge(iplImage);
    }
}

void MainWindow::slotHoughCircleEdge(){
    if(iplImage!=0){
        opencvFun->houghCircleEdge(iplImage);
    }
}
void MainWindow::slotBinarySegment(){
    if(iplImage!=0){
        opencvFun->binarySegment(iplImage);
    }
}
void MainWindow::slotOtsuSegment(){
    if(iplImage!=0){
        opencvFun->otsuSegment(iplImage);
    }
}
void MainWindow::slotAdaptiveSegment(){
    if(iplImage!=0){
        opencvFun->adaptiveSegment(iplImage);
    }
}
void MainWindow::slotMeanShiftSegment(){
    if(iplImage!=0){
        opencvFun->meanShiftSegment(iplImage);
    }
}

void MainWindow::slotPyrSegment(){
    if(iplImage!=0){
        opencvFun->pyrSegment(iplImage);
    }
}

void MainWindow::slotColorWeight(){
    ColorWeightDialog *dialog=new ColorWeightDialog(opencvFun->getRedWeight(),opencvFun->getGreenWeight(),opencvFun->getBlueWeight());
    if(dialog->exec()==QDialog::Accepted){
        opencvFun->setWeight(dialog->redWeight(),dialog->greenWeight(),dialog->blueWeight());
        QMessageBox::information(this,trUtf8("提示"),trUtf8("设置通道权值成功！"));
    }
}

void MainWindow::slotFillColor(){
    imageItem->setSelectType(2);
    imageItem->setCursor(Qt::CrossCursor);
}

void MainWindow::slotFillArea(){
    imageItem->setSelectType(1);
    imageItem->setCursor(Qt::CrossCursor);
}

void MainWindow::slotFillAreaPoint(int x, int y){
    if(iplImage!=0){
        QColor color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);
        if (color.isValid()) {
            int r,g,b;
            color.getRgb(&r,&g,&b);
            opencvFun->floodFillSegment(iplImage,x,y,r,g,b);
        }
    }
    imageItem->setSelectType(0);
    imageItem->setCursor(Qt::OpenHandCursor);
}

void MainWindow::slotFillColorPoint(int x, int y){
    if(iplImage!=0){
        QColor color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);
        if (color.isValid()) {
            int r,g,b;
            color.getRgb(&r,&g,&b);
            opencvFun->fillColorSegment(iplImage,x,y,r,g,b);
        }
    }
    imageItem->setSelectType(0);
    imageItem->setCursor(Qt::OpenHandCursor);
}

void MainWindow::slotConvertGray(){
    if(iplImage!=0){
        opencvFun->convert2Gray(iplImage);
    }
}

void MainWindow::sceneRefresh(){
    imageItem->setPixmap(QPixmap::fromImage(*qImage));
    imageItem->setOffset(2500-qImage->width()/2,2500-qImage->height()/2);
}

void MainWindow::slotExit(){
    qApp->exit();
}
void MainWindow::slotOpenFile(){
    QString filename = QFileDialog::getOpenFileName(this);
    if (!filename.isEmpty()){
        statusBar()->showMessage(trUtf8("打开文件：")+filename);
        mainImage= cvLoadImage(qPrintable(filename));
        copyImage();
    }else{
        statusBar()->showMessage(trUtf8("未选择打开文件！"));
    }
}
void MainWindow::slotReloadFile(){
    copyImage();
}
void MainWindow::copyImage(){
    if(mainImage!=0){
        if(iplImage!=0){
            cvReleaseImage(&iplImage);
            delete qImage;
        }
        iplImage= cvCreateImage(cvGetSize(mainImage),mainImage->depth,mainImage->nChannels);
        if (mainImage->origin == IPL_ORIGIN_TL){
            cvCopy(mainImage,iplImage,0);
        }else{
            cvFlip(mainImage,iplImage,0);
        }
        iplImage2QImage();
        sceneRefresh();
    }
}
