#ifndef IMAGEPROCESS_HPP
#define IMAGEPROCESS_HPP

#include <QThread>
#include <QImage>
#include <QPixmap>
#include <QString>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "alpr.h"


class ThreadManager;


class ImageProcess : public QThread
{
    Q_OBJECT
public:
    ImageProcess(ThreadManager* tmanager);
    ~ImageProcess() override;

    void run() override;

signals:
    void sendPlateString(QString);
    void getFrame(cv::Mat*);
public slots:
    void stopThread();
private slots:
    void startThread();

private:
    ThreadManager* m_tmanager;
    bool m_keepRunning = true;
    alpr::Alpr m_openalpr = alpr::Alpr("eu","openalpr.conf");


    void testOpenALPR();


    QImage qt_image;
    cv::Mat m_frame;
};

#endif // IMAGEPROCESS_HPP
