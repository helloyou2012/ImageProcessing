#include "OpencvFunction.h"


OpencvFunction::OpencvFunction(QObject *parent) :
    QObject(parent)
{
    b_w=0.587;
    g_w=0.299;
    r_w=0.114;
}
void OpencvFunction::medianSmooth(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvSmooth(dist,dist,CV_MEDIAN,3);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}
void OpencvFunction::gaussianSmooth(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvSmooth(dist,dist,CV_GAUSSIAN,3,3);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}
void OpencvFunction::bilateralSmooth(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvSmooth(dist,dist,CV_BILATERAL,3,3,11,11);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}
void OpencvFunction::dilate(IplImage *src){
    int an = 2;
    IplConvKernel* element = cvCreateStructuringElementEx(an*2+1,an*2+1,an,an,CV_SHAPE_ELLIPSE,0);
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvDilate(dist,dist,element,1);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::erode(IplImage *src){
    int an = 2;
    IplConvKernel* element = cvCreateStructuringElementEx(an*2+1,an*2+1,an,an,CV_SHAPE_ELLIPSE,0);
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvErode(dist,dist,element,1);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}
void OpencvFunction::openingMorphology(IplImage *src){
    int an = 2;
    IplConvKernel* element = cvCreateStructuringElementEx(an*2+1,an*2+1,an,an,CV_SHAPE_ELLIPSE,0);
    IplImage *dist = NULL;
    IplImage *tmp=NULL;
    if(src != NULL){
        tmp = cvCreateImage(cvGetSize(src),8,1);
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvMorphologyEx(dist,dist,tmp,element,CV_MOP_OPEN,1);
        emit processComplete(dist);
        cvReleaseImage(&tmp);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::closingMorphology(IplImage *src){
    int an = 2;
    IplConvKernel* element = cvCreateStructuringElementEx(an*2+1,an*2+1,an,an,CV_SHAPE_ELLIPSE,0);
    IplImage *dist = NULL;
    IplImage *tmp=NULL;
    if(src != NULL){
        tmp = cvCreateImage(cvGetSize(src),8,1);
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvMorphologyEx(dist,dist,tmp,element,CV_MOP_CLOSE,1);
        emit processComplete(dist);
        cvReleaseImage(&tmp);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::tophatMorphology(IplImage *src){
    int an = 3;
    IplConvKernel* element = cvCreateStructuringElementEx(an*2+1,an*2+1,an,an,CV_SHAPE_ELLIPSE,0);
    IplImage *dist = NULL;
    IplImage *tmp=NULL;
    if(src != NULL){
        tmp = cvCreateImage(cvGetSize(src),8,1);
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvMorphologyEx(dist,dist,tmp,element,CV_MOP_TOPHAT,1);
        emit processComplete(dist);
        cvReleaseImage(&tmp);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::bothatMorphology(IplImage *src){
    int an = 3;
    IplConvKernel* element = cvCreateStructuringElementEx(an*2+1,an*2+1,an,an,CV_SHAPE_ELLIPSE,0);
    IplImage *dist = NULL;
    IplImage *tmp=NULL;
    if(src != NULL){
        tmp = cvCreateImage(cvGetSize(src),8,1);
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvMorphologyEx(dist,dist,tmp,element,CV_MOP_BLACKHAT,1);
        emit processComplete(dist);
        cvReleaseImage(&tmp);
        cvReleaseImage(&dist);
    }
}
void OpencvFunction::sobelEdge(IplImage *src){
    IplImage *dist = NULL;
    IplImage *tmp = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),IPL_DEPTH_32F,1);
        tmp = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            cvCvtColor(src,tmp,CV_RGB2GRAY);
        }else{
            cvCopy(src,tmp,0);
        }
        cvScale(tmp,dist);
        cvSobel(dist, dist,1,1, 3);
        emit processComplete(dist);
        cvReleaseImage(&tmp);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::cannyEdge(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvCanny(dist,dist, 50, 150, 3);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::laplaceEdge(IplImage *src){
    IplImage *dist = NULL;
    IplImage *tmp = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),IPL_DEPTH_32F,1);
        tmp = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            cvCvtColor(src,tmp,CV_RGB2GRAY);
        }else{
            cvCopy(src,tmp,0);
        }
        cvScale(tmp,dist);
        cvLaplace(dist,dist,1);
        emit processComplete(dist);
        cvReleaseImage(&tmp);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::houghCircleEdge(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvEqualizeHist(dist,dist);
        cvSmooth(dist,dist,CV_GAUSSIAN,3,3);
        CvMemStorage* storage = cvCreateMemStorage(0);
        CvSeq* circles = cvHoughCircles(dist,storage,CV_HOUGH_GRADIENT, 2,dist->height/10,100,100,50,130);
        for(int i = 0; i < circles->total; i++ ){
            float* p = (float*)cvGetSeqElem(circles,i);
            cvCircle(src,cvPoint(cvRound(p[0]),cvRound(p[1])), 3, CV_RGB(0,255,0), -1, 8, 0 );
            cvCircle(src,cvPoint(cvRound(p[0]),cvRound(p[1])), cvRound(p[2]), CV_RGB(255,0,0), 3, 8, 0);
        }
        emit processComplete(src);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::binaryThreshold(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvThreshold(dist, dist, 128, 255, CV_THRESH_BINARY);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::otsuThreshold(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvThreshold(dist, dist, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}
void OpencvFunction::adaptiveThreshold(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvAdaptiveThreshold(dist, dist, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}
void OpencvFunction::histequal(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvEqualizeHist(dist,dist);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}
void OpencvFunction::binarySegment(IplImage *src){
    CvMemStorage * storage = cvCreateMemStorage(0);
    CvSeq * contour = 0;
    int mode = CV_RETR_CCOMP;
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvEqualizeHist(dist,dist);
        cvThreshold(dist, dist, 128, 255, CV_THRESH_BINARY);
        cvFindContours(dist, storage,&contour, sizeof(CvContour),mode);
        //cvDrawContours(src, contour,CV_RGB(255,255,255),CV_RGB(255,255,255),5);

        detectRects(src,contour);
        emit processComplete(src);
        cvReleaseImage(&dist);
    }
    cvReleaseMemStorage(&storage);
}

void OpencvFunction::otsuSegment(IplImage *src){
    CvMemStorage * storage = cvCreateMemStorage(0);
    CvSeq * contour = 0;
    int mode = CV_RETR_CCOMP;
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvEqualizeHist(dist,dist);
        cvThreshold(dist, dist, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
        cvFindContours(dist, storage,&contour, sizeof(CvContour),mode);
        //cvDrawContours(src, contour,CV_RGB(255,255,255),CV_RGB(255,255,255),5);

        detectRects(src,contour);
        emit processComplete(src);
        cvReleaseImage(&dist);
    }
    cvReleaseMemStorage(&storage);
}

void OpencvFunction::adaptiveSegment(IplImage *src){
    CvMemStorage * storage = cvCreateMemStorage(0);
    CvSeq * contour = 0;
    int mode = CV_RETR_CCOMP;
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        cvEqualizeHist(dist,dist);
        cvAdaptiveThreshold(dist, dist, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C);
        cvFindContours(dist, storage,&contour, sizeof(CvContour),mode);
        //cvDrawContours(src, contour,CV_RGB(255,255,255),CV_RGB(255,255,255),5);

        detectRects(src,contour);
        emit processComplete(src);
        cvReleaseImage(&dist);
    }
    cvReleaseMemStorage(&storage);
}
void OpencvFunction::detectRects(IplImage*iplImg,CvSeq * contour){
    QVector<QRect> *detectRect=new QVector<QRect>();
    while(contour!= NULL)
    {
        double area=fabs(cvContourArea(contour,CV_WHOLE_SEQ));
        if(area<400||area>22500){
            contour = contour->h_next;
            continue;
        }
        int num=contour->total;
        CvMat *mat_contour = cvCreateMat(1,num,CV_32FC2);
        CvPoint2D32f *ptr_mat=(CvPoint2D32f*)(mat_contour->data.ptr);
        for(int i = 0; i < num; ++i){
            CvPoint *p = (CvPoint*)cvGetSeqElem(contour, i);
            *ptr_mat=cvPointTo32f(*p);
            ptr_mat++;
        }
        CvRect rect = cvBoundingRect(mat_contour);
        drawRect(iplImg,rect);
        int w=rect.width<rect.height?rect.height:rect.width;
        QRect qrect;
        qrect.setX(rect.x);
        qrect.setY(rect.y);
        qrect.setWidth(w);
        qrect.setHeight(w);
        (*detectRect)<<qrect;
        contour = contour->h_next;
    }
    emit detectComplete(detectRect);
}
void OpencvFunction::drawRect(IplImage*iplImg,CvRect &rect){
    cvRectangle(iplImg,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),cvScalar(0xff,0xff,0xff),2);
}

void OpencvFunction::meanShiftSegment(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
        cvCopy(src,dist,0);
        int spatialRad = 10;
        int colorRad = 10;
        int maxPyrLevel = 1;
        cvPyrMeanShiftFiltering(dist,dist,spatialRad,colorRad,maxPyrLevel);
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}
void OpencvFunction::pyrSegment(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        CvMemStorage* storage = cvCreateMemStorage(0);
        CvSeq* comp = NULL;
        int w=src->width/16*16;
        int h=src->height/16*16;
        dist = cvCreateImage(cvSize(w,h),src->depth,src->nChannels);
        cvResize(src,dist);
        cvPyrSegmentation(dist,dist, storage, &comp, 4, 150, 30 );
        int n_comp = comp->total;
        for( int i=0; i<n_comp; i++ ) {
            CvConnectedComp* cc = (CvConnectedComp*) cvGetSeqElem( comp, i );
            cvDrawContours(dist,cc->contour,CV_RGB(255,255,255),CV_RGB(255,255,255),5);
        }
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::floodFillSegment(IplImage *src,int x,int y,int r,int g,int b){
    IplImage *dist=NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
        cvCopy(src,dist,0);
        cvFloodFill(dist,cvPoint(x,y),CV_RGB(r,g,b),cvScalarAll(0),cvScalarAll(0));
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::fillColorSegment(IplImage *src, int x, int y, int r, int g, int b){
    IplImage *dist=NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
        cvCopy(src,dist,0);
        CvScalar ns=cvScalar(r,g,b);
        CvScalar s = cvGet2D(dist,y,x);
        for(int i=0;i<dist->height;i++){
            for(int j=0;j<dist->width;j++){
                CvScalar t=cvGet2D(dist,i,j);
                if(s.val[0]==t.val[0]&&s.val[1]==t.val[1]&&s.val[2]==t.val[2])
                    cvSet2D(dist,i,j,ns);
            }
        }
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::convert2Gray(IplImage *src){
    IplImage *dist = NULL;
    if(src != NULL){
        dist = cvCreateImage(cvGetSize(src),8,1);
        if(src->nChannels == 3) {
            color2Gray(src,dist);
        }else{
            cvCopy(src,dist,0);
        }
        emit processComplete(dist);
        cvReleaseImage(&dist);
    }
}

void OpencvFunction::color2Gray(IplImage *src,IplImage *dist){
    IplImage *r=cvCreateImage(cvGetSize(src), src->depth, 1);
    IplImage *g=cvCreateImage(cvGetSize(src), src->depth, 1);
    IplImage *b=cvCreateImage(cvGetSize(src), src->depth, 1);
    cvSplit(src,b,g,r,NULL);
    cvAddWeighted(b,b_w,g,g_w,0,g);
    cvAddWeighted(g,1,r,r_w,0,r);
    cvScale(r,dist);
    cvReleaseImage(&r);
    cvReleaseImage(&g);
    cvReleaseImage(&b);
}

void OpencvFunction::setWeight(double rw,double gw,double bw){
    r_w=rw;
    g_w=gw;
    b_w=bw;
}
double OpencvFunction::getRedWeight(){
    return r_w;
}

double OpencvFunction::getGreenWeight(){
    return g_w;
}

double OpencvFunction::getBlueWeight(){
    return b_w;
}

