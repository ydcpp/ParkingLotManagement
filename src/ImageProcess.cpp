#include "ImageProcess.hpp"
#include "ThreadManager.hpp"
#include "CameraStream.hpp"

#include <alpr.h>

#include <QDebug>


ImageProcess::ImageProcess(ThreadManager* tmanager, CameraStream* cam)
    : m_tmanager(tmanager), m_camera(cam)
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

    m_frame = convertImage(m_camera->captureImage(),true);

    if(m_frame.empty()){
        qDebug() << "Could not retrieve a frame to process.";
        return;
    }

    cv::imshow("captured frame",m_frame);
    cv::waitKey(0);

    // Recognize an image file.  You could alternatively provide the image bytes in-memory.
    //alpr::AlprResults results = openalpr.recognize("./test.tif");
    std::vector<alpr::AlprRegionOfInterest> emptyRoi;
    alpr::AlprResults results = openalpr.recognize(m_frame.data,(quint32)m_frame.elemSize(),m_frame.cols,m_frame.rows,emptyRoi);
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
    emit sendPlateString("");
    this->quit();
}

void ImageProcess::startThread(const QImage& image)
{
    if(this->isRunning()) this->quit();
    qt_image = image;
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

cv::Mat ImageProcess::convertImage(QImage inImage, bool inCloneImageData)
{
    switch ( inImage.format() )
          {
             // 8-bit, 4 channel
             case QImage::Format_ARGB32:
             case QImage::Format_ARGB32_Premultiplied:
             {
                cv::Mat  mat( inImage.height(), inImage.width(),
                              CV_8UC4,
                              const_cast<uchar*>(inImage.bits()),
                              static_cast<size_t>(inImage.bytesPerLine())
                              );

                return (inCloneImageData ? mat.clone() : mat);
             }

             // 8-bit, 3 channel
             case QImage::Format_RGB32:
             {
                if ( !inCloneImageData )
                {
                   qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning so we don't modify the original QImage data";
                }

                cv::Mat  mat( inImage.height(), inImage.width(),
                              CV_8UC4,
                              const_cast<uchar*>(inImage.bits()),
                              static_cast<size_t>(inImage.bytesPerLine())
                              );

                cv::Mat  matNoAlpha;

                cv::cvtColor( mat, matNoAlpha, cv::COLOR_BGRA2BGR );   // drop the all-white alpha channel

                return matNoAlpha;
             }

             // 8-bit, 3 channel
             case QImage::Format_RGB888:
             {
                if ( !inCloneImageData )
                {
                   qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning so we don't modify the original QImage data";
                }

                QImage   swapped = inImage.rgbSwapped();

                return cv::Mat( swapped.height(), swapped.width(),
                                CV_8UC3,
                                const_cast<uchar*>(swapped.bits()),
                                static_cast<size_t>(swapped.bytesPerLine())
                                ).clone();
             }

             // 8-bit, 1 channel
             case QImage::Format_Indexed8:
             {
                cv::Mat  mat( inImage.height(), inImage.width(),
                              CV_8UC1,
                              const_cast<uchar*>(inImage.bits()),
                              static_cast<size_t>(inImage.bytesPerLine())
                              );

                return (inCloneImageData ? mat.clone() : mat);
             }

             default:
                qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
                break;
          }

    return cv::Mat();
}


