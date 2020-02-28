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
        if (!m_openalpr.isLoaded())
        {
            qDebug() << "OpenALPR is not loaded.";
            break;
        }
        emit getFrame(&m_frame);
        cv::waitKey(1000);
        if(m_frame.empty()){
            qDebug() << "frame is empty.";
            cv::waitKey(1000);
            continue;
        }
        cv::waitKey(1000);
        alpr::AlprResults results = m_openalpr.recognize("./assets/other/alpr_test_data/7.jpg");
        if(results.plates.empty()){
            qDebug() << "Plate could not be recognized.";
            emit sendPlateString(" - ");
            continue;
        }
        alpr::AlprPlateResult plateResult = results.plates[0];
        QString plateresult = QString::fromStdString(plateResult.bestPlate.characters);
        emit sendPlateString(plateresult + " - " + QString::number(test++));
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


