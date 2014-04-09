#ifndef OPENCVFUNCTION_H
#define OPENCVFUNCTION_H

#include <QObject>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QVector>
#include <QRect>

using namespace cv;

class OpencvFunction : public QObject
{
    Q_OBJECT
public:
    explicit OpencvFunction(QObject *parent = 0);
    void medianSmooth(IplImage *src);
    void gaussianSmooth(IplImage *src);
    void bilateralSmooth(IplImage *src);
    void dilate(IplImage *src);
    void erode(IplImage *src);
    void openingMorphology(IplImage *src);
    void closingMorphology(IplImage *src);
    void tophatMorphology(IplImage *src);
    void bothatMorphology(IplImage *src);
    void sobelEdge(IplImage *src);
    void cannyEdge(IplImage *src);
    void laplaceEdge(IplImage *src);
    void houghCircleEdge(IplImage *src);
    void binaryThreshold(IplImage *src);
    void otsuThreshold(IplImage *src);
    void adaptiveThreshold(IplImage *src);
    void binarySegment(IplImage *src);
    void otsuSegment(IplImage *src);
    void adaptiveSegment(IplImage *src);
    void histequal(IplImage *src);
    void meanShiftSegment(IplImage *src);
    void pyrSegment(IplImage *src);
    void floodFillSegment(IplImage *src,int x,int y,int r,int g,int b);
    void fillColorSegment(IplImage *src,int x,int y,int r,int g,int b);
    void color2Gray(IplImage *src,IplImage *dist);
    void convert2Gray(IplImage *src);
    void setWeight(double rw,double gw,double bw);
    double getRedWeight();
    double getGreenWeight();
    double getBlueWeight();
    void detectRects(IplImage*iplImg,CvSeq * contour);
    void drawRect(IplImage*iplImg,CvRect &rect);

signals:
    void processComplete(IplImage*ipldist);
    void detectComplete(QVector<QRect> *rects);
public slots:
private:
    double r_w;
    double g_w;
    double b_w;
};

#endif // OPENCVFUNCTION_H
