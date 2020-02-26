#include "ImageProcess.hpp"
#include "ThreadManager.hpp"


#include <QDebug>

using namespace cv;

ImageProcess::ImageProcess(ThreadManager* tmanager)
    : m_tmanager(tmanager)
{
    connect(m_tmanager,&ThreadManager::readPlateVehicle,this,&ImageProcess::startThread);
    connect(m_tmanager,&ThreadManager::stopImageProcessing,this,&ImageProcess::stopThread);
}

ImageProcess::~ImageProcess()
{
    stopThread();
}

void ImageProcess::run()
{
    m_keepRunning = true;
    m_frame.release();
    unsigned int test = 0;
    while(m_keepRunning)
    {
        waitKey(1000);
        emit getFrame(&m_frame);
        if(m_frame.empty()){
            qDebug() << "frame is empty.";
            waitKey(1000);
            continue;
        }
        /* do image processing with m_frame and read the license plate */
        emit sendPlateString("deneme" + QString::number(test++));
        waitKey(1000);
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
