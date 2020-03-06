#include "ImageProcess.hpp"
#include "ThreadManager.hpp"



#include <QDebug>



using namespace cv;

ImageProcess::ImageProcess(ThreadManager* tmanager)
    : m_tmanager(tmanager)
{
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
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (m_tessapi->Init(NULL, "tur")) {
        qDebug() << "Could not initialize tesseract.";
        return;
    }
    if(m_frame.empty()){
        qDebug() << "frame is empty.";
        emit sendPlateString(" - ");
        while(m_frame.empty()){ }
    }
    emit sendPlateString("Processing...");
    cv::Mat licensePlate;
    //TODO extract plate region and send thresholded image to tesseract
    licensePlate = m_frame;
    //Get OCR result
    m_tessapi->SetImage((uchar*)licensePlate.data, licensePlate.size().width, licensePlate.size().height, licensePlate.channels(), (int)licensePlate.step1());
    m_tessapi->SetSourceResolution(70); //1280x720 ppi=70, 1920x1080 ppi=100
    m_outText = m_tessapi->GetUTF8Text();
    QString resultplate = QString::fromStdString(m_outText);
    emit sendPlateString(resultplate);
    m_frame.release();
    m_tessapi->End();
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
    m_tessapi->End();
}



