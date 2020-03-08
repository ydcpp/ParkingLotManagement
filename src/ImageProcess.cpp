#include "ImageProcess.hpp"
#include "ThreadManager.hpp"
#include <alpr.h>

#include <QDebug>



ImageProcess::ImageProcess(ThreadManager* tmanager)
    : m_tmanager(tmanager)
{
    connect(m_tmanager,&ThreadManager::stopThreads,this,&ImageProcess::stopThread);
    connect(m_tmanager,&ThreadManager::terminateThreads,this,&ImageProcess::terminateThread);
}

ImageProcess::~ImageProcess()
{
    terminateThread();
    if(m_outText) delete [] m_outText;
}

void ImageProcess::run()
{
    emit sendPlateString("Processing...");
    alpr::Alpr openalpr("eu", "./openalpr.conf");
    openalpr.setDefaultRegion("tr");

    if (openalpr.isLoaded() == false)
    {
        qDebug() << "Error loading OpenALPR";
        emit sendPlateString(" ERROR ");
        return;
    }
    if(m_frame.empty()){
        qDebug() << "Could not retrieve a frame to process.";
        return;
    }

    // Recognize an image file.  You could alternatively provide the image bytes in-memory.
    alpr::AlprResults results = openalpr.recognize("./test.tif");
    //std::vector<alpr::AlprRegionOfInterest> emptyRoi;
    //alpr::AlprResults results = openalpr.recognize(m_frame.data,m_frame.elemSize(),m_frame.cols,m_frame.rows,emptyRoi);
    if(results.plates.empty()){
        qDebug() << "Could not find a plate.";
        emit sendPlateString(" - ");
        return;
    }
    alpr::AlprPlateResult plate = results.plates[0];
    QString resultplate = QString::fromStdString(plate.topNPlates[0].characters);
    emit sendPlateString(resultplate);

    // Iterate through the results.  There may be multiple plates in an image,
    // and each plate return sthe top N candidates.
//    for (unsigned int i = 0; i < results.plates.size(); i++)
//    {
//      alpr::AlprPlateResult plate = results.plates[i];
//      qDebug() << "plate" << i << ": " << plate.topNPlates.size() << " results";

//        for (unsigned int k = 0; k < plate.topNPlates.size(); k++)
//        {
//          alpr::AlprPlate candidate = plate.topNPlates[k];
//          qDebug() << "    - " << QString::fromStdString(candidate.characters) << "\t confidence: " << candidate.overall_confidence;
//          qDebug() << "\t pattern_match: " << candidate.matches_template;
//        }
//    }
}

void ImageProcess::stopThread()
{
    this->quit();
}

void ImageProcess::startThread(cv::Mat& frameToProcess)
{
    m_frame = frameToProcess;
    this->start();
}

void ImageProcess::terminateThread()
{
    this->quit();
    wait(100);
    if(this->isRunning()){
        this->terminate();
        wait();
    }
}



