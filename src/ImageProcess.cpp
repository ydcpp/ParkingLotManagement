#include "ImageProcess.hpp"
#include "ThreadManager.hpp"





#include <QDebug>



using namespace cv;

ImageProcess::ImageProcess(ThreadManager* tmanager)
    : m_tmanager(tmanager)
{
    connect(m_tmanager,&ThreadManager::startThreads,this,&ImageProcess::startThread);
    connect(m_tmanager,&ThreadManager::stopThreads,this,&ImageProcess::stopThread);
    connect(m_tmanager,&ThreadManager::terminateThreads,this,&ImageProcess::terminateThread);
    m_tessapi = new tesseract::TessBaseAPI();
}

ImageProcess::~ImageProcess()
{
    terminateThread();
    if(m_outText) delete [] m_outText;
    if(m_image) pixDestroy(&m_image);
    delete m_tessapi;
}

void ImageProcess::run()
{
    m_keepRunning = true;
    m_frame.release();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (m_tessapi->Init(NULL, "tur")) {
        qDebug() << "Could not initialize tesseract.";
        return;
    }
    while(m_keepRunning){
        emit getFrame(&m_frame);

        cv::waitKey(1000);
        if(m_frame.empty()){
            qDebug() << "frame is empty.";
            cv::waitKey(1000);
            continue;
        }
        cv::waitKey(1000);
        // Open input image with leptonica library
        m_image = pixRead("test.tif");
        m_tessapi->SetImage(m_image);
        // Get OCR result
        m_outText = m_tessapi->GetUTF8Text();
        QString resultplate = QString::fromStdString(m_outText);
        emit sendPlateString(resultplate);
    }
    m_tessapi->End();
}

void ImageProcess::stopThread()
{
    m_keepRunning = false;
}

void ImageProcess::startThread()
{
    this->start();
}

void ImageProcess::terminateThread()
{
    m_keepRunning = false;
    wait(1000);
    if(this->isRunning()){
        this->terminate();
        wait(1000);
    }
    m_tessapi->End();
}



