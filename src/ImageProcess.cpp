#include "ImageProcess.hpp"
#include "ThreadManager.hpp"


#include <QDebug>

using namespace cv;

ImageProcess::ImageProcess(ThreadManager* tmanager)
    : m_tmanager(tmanager)
{

}

ImageProcess::~ImageProcess()
{
    stopThread();
}

void ImageProcess::run()
{
    m_keepRunning = true;
    unsigned int test = 0;
    while(m_keepRunning)
    {
        waitKey(100);
        m_frame = emit getFrame();
        /* do image processing and plate reading */
        emit sendPlateString("deneme" + QString::number(test++));
        waitKey(2000);
    }
}

void ImageProcess::stopThread()
{
    m_keepRunning = false;
    wait(1000);
    if(this->isRunning()){
        this->terminate();
        wait(1000);
    }
}

void ImageProcess::startThread()
{
    this->start();
}
