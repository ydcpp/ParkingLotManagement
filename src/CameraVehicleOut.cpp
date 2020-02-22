#include "CameraVehicleOut.hpp"
#include "ThreadManager.hpp"
#include "applicationwindow.hpp"

#include <stdint.h>


#include <QDebug>

using namespace cv;

CameraVehicleOut::CameraVehicleOut(ThreadManager* tmanager)
    : m_tmanager(tmanager)
{
    connect(this,&CameraVehicleOut::updateCameraDisplay_vehicle_out,tmanager->getAppWindow(),&ApplicationWindow::drawCamInput_vehicle_out);
}

CameraVehicleOut::~CameraVehicleOut()
{
    stopCameraStream();
}

int CameraVehicleOut::getFPS() const
{
    return m_MaxFPS;
}

void CameraVehicleOut::setFPS(int value)
{
    m_MaxFPS = value;
}


void CameraVehicleOut::run()
{
    m_vidcap.open(1);
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
            emit updateCameraDisplay_vehicle_out(QPixmap::fromImage(qt_image));
        }
        qDebug() << "Video stream is stopped.";
        m_vidcap.release();
    }
}

void CameraVehicleOut::stopCameraStream()
{
    m_keepStreaming = false;
    wait(1000);
}

void CameraVehicleOut::startThread()
{
    this->start();
}

