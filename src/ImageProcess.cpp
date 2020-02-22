#include "ImageProcess.hpp"
#include "ThreadManager.hpp"

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
    while(m_keepRunning){
        /* process */
    }
}

void ImageProcess::stopThread()
{
    m_keepRunning = false;
    wait(1000);
}

void ImageProcess::startThread()
{
    this->start();
}
