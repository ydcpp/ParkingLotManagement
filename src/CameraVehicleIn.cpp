#include "CameraVehicleIn.hpp"
#include "ThreadManager.hpp"
#include "applicationwindow.hpp"

#include <stdint.h>


#include <QDebug>

using namespace cv;

CameraVehicleIn::CameraVehicleIn(ThreadManager* tmanager)
    : m_tmanager(tmanager)
{
    connect(this,&CameraVehicleIn::updateCameraDisplay_vehicle_in,tmanager->getAppWindow(),&ApplicationWindow::drawCamInput_vehicle_in);
}

int CameraVehicleIn::getFPS() const
{
    return m_MaxFPS;
}

void CameraVehicleIn::setFPS(int value)
{
    m_MaxFPS = value;
}


void CameraVehicleIn::run()
{
    m_vidcap.open(0);
    if(!m_vidcap.isOpened()){
        qDebug() << "camera is not open.";
    }else{
        m_keepStreaming = true;
        qDebug() << "Video stream is started.";
        while(m_keepStreaming){
            m_vidcap >> frame;
            cvtColor(frame,frame,COLOR_BGR2RGB);
            qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
            waitKey(1000/m_MaxFPS);
            emit updateCameraDisplay_vehicle_in(QPixmap::fromImage(qt_image));
        }
        qDebug() << "Video stream is stopped.";
        m_vidcap.release();
    }
}

void CameraVehicleIn::stopCameraStream()
{
    m_keepStreaming = false;
    wait(1000);
}

void CameraVehicleIn::startThread()
{
    this->start();
}


