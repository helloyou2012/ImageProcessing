#include <QtGui/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(ImageProcessing);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
	// Hongyi bug fixed.

    return a.exec();
}
