#include "CameraStream.hpp"
#include "ThreadManager.hpp"
#include "applicationwindow.hpp"


#include <QDebug>

using namespace cv;

CameraStream::CameraStream(ThreadManager* tmanager, unsigned int cameraIndex)
    : m_tmanager(tmanager), m_camIndex(cameraIndex)
{
    connect(m_tmanager,&ThreadManager::startThreads,this,&CameraStream::startThread);
    connect(m_tmanager,&ThreadManager::stopThreads,this,&CameraStream::stopThread);
    connect(m_tmanager,&ThreadManager::terminateThreads,this,&CameraStream::terminateThread);
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
//    m_vidcap.open("assets/other/testvid.mp4");
    m_vidcap.open(m_camIndex);
    if(!m_vidcap.isOpened()){
        qDebug() << "camera on device index (" <<  m_camIndex << ") could not open.";
        emit cameraIsClosed();
    }else{
        emit cameraIsOpen();
        m_keepStreaming = true;
        qDebug() << "Video stream from camera device (" << m_camIndex << ") is started.";
        while(m_vidcap.read(m_frame) && m_keepStreaming){
            cvtColor(m_frame,m_frame,COLOR_BGR2RGB);
            qt_image = QImage((const unsigned char*) (m_frame.data), m_frame.cols, m_frame.rows, QImage::Format_RGB888);
            emit updateCameraDisplay(QPixmap::fromImage(qt_image));
            waitKey(1000/m_MaxFPS);
        }
        m_frame.release();
        m_vidcap.release();
        qDebug() << "Video stream is stopped.(" << m_camIndex << ")";
        emit cameraIsClosed();
    }
}

void CameraStream::getCurrentFrame(cv::Mat* frame)
{
    *frame = m_frame;
}

void CameraStream::stopThread()
{
    m_keepStreaming = false;
}

void CameraStream::startThread()
{
    this->start();
}

void CameraStream::terminateThread()
{
    m_keepStreaming = false;
    wait(100);
    if(this->isRunning()){
        this->terminate();
        wait();
    }
}


