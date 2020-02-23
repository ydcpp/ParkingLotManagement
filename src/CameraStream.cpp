#include "CameraStream.hpp"
#include "ThreadManager.hpp"
#include "applicationwindow.hpp"


#include <QDebug>

using namespace cv;

CameraStream::CameraStream(ThreadManager* tmanager, unsigned int cameraIndex)
    : m_tmanager(tmanager), m_camIndex(cameraIndex)
{
}

int CameraStream::getFPS() const
{
    return m_MaxFPS;
}

void CameraStream::setFPS(int value)
{
    m_MaxFPS = value;
}


void CameraStream::run()
{
    m_vidcap.open(m_camIndex);
    if(!m_vidcap.isOpened()){
        qDebug() << "camera on device index (" <<  m_camIndex << ") could not open.";
        emit updateCamStatusText("Kamera kapalı", "color:red;");
    }else{
        emit updateCamStatusText("Kamera açık", "color:green;");
        m_keepStreaming = true;
        qDebug() << "Video stream from camera device (" << m_camIndex << ") is started.";
        while(m_keepStreaming){
            m_vidcap >> frame;
            emit captureLicensePlate(frame);
            cvtColor(frame,frame,COLOR_BGR2RGB);
            qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
            waitKey(1000/m_MaxFPS);
            emit updateCameraDisplay(QPixmap::fromImage(qt_image));
        }
        qDebug() << "Video stream is stopped.(" << m_camIndex << ")";
        m_vidcap.release();
        emit updateCamStatusText("Kamera kapalı", "color:red;");
    }
}

void CameraStream::stopCameraStream()
{
    m_keepStreaming = false;
    wait(1000);
    if(this->isRunning()){
        this->terminate();
        wait(1000);
    }
}

void CameraStream::startThread()
{
    this->start();
}


