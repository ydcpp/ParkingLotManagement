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
    while(m_keepRunning)
    {
        m_frame = emit getFrame();
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
