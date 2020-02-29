#include "ThreadManager.hpp"

#include "applicationwindow.hpp"
#include "CameraStream.hpp"
#include "ImageProcess.hpp"

#include <QTimer>
#include <QMetaType>

ThreadManager* ThreadManager::m_instance(0);

ThreadManager::ThreadManager(ApplicationWindow* appwindow, unsigned int vehicle_in_CamIndex, unsigned int vehicle_out_CamIndex) : m_appwindow(appwindow)
{
    m_camVehicleIn = new CameraStream(this, vehicle_in_CamIndex);
    m_camVehicleOut = new CameraStream(this, vehicle_out_CamIndex);
    m_plateReaderVehicleIn = new ImageProcess(this);
    m_plateReaderVehicleOut = new ImageProcess(this);
    connect(m_appwindow,&ApplicationWindow::stopAllThreads,this,&ThreadManager::stopAllThreads);
    connect(m_appwindow,&ApplicationWindow::terminateAllThreads,this,&ThreadManager::terminateAllThreads);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    // incoming vehicles camera setup
    connect(m_camVehicleIn,&CameraStream::updateCameraDisplay,m_appwindow,&ApplicationWindow::drawCamInput_vehicle_in);
    connect(m_camVehicleIn,&CameraStream::captureLicensePlate,this,&ThreadManager::capturedFrame_vehicle_in);
    connect(m_camVehicleIn,&CameraStream::cameraIsOpen,m_appwindow,&ApplicationWindow::openCameraStream_in);
    connect(m_camVehicleIn,&CameraStream::cameraIsClosed,m_appwindow,&ApplicationWindow::closeCameraStream_in);
    connect(m_camVehicleIn,&CameraStream::cameraIsClosed,m_plateReaderVehicleIn,&ImageProcess::stopThread);
    // outgoing vehicles camera setup
    connect(m_camVehicleOut,&CameraStream::updateCameraDisplay,m_appwindow,&ApplicationWindow::drawCamInput_vehicle_out);
    connect(m_camVehicleOut,&CameraStream::captureLicensePlate,this,&ThreadManager::capturedFrame_vehicle_out);
    connect(m_camVehicleOut,&CameraStream::cameraIsOpen,m_appwindow,&ApplicationWindow::openCameraStream_out);
    connect(m_camVehicleOut,&CameraStream::cameraIsClosed,m_appwindow,&ApplicationWindow::closeCameraStream_out);
    connect(m_camVehicleOut,&CameraStream::cameraIsClosed,m_plateReaderVehicleOut,&ImageProcess::stopThread);
    // image process thread setup
    connect(m_plateReaderVehicleIn,&ImageProcess::sendPlateString,m_appwindow,&ApplicationWindow::displayLicensePlateString_vehicle_in);
    connect(m_plateReaderVehicleOut,&ImageProcess::sendPlateString,m_appwindow,&ApplicationWindow::displayLicensePlateString_vehicle_out);
    connect(m_plateReaderVehicleIn,&ImageProcess::getFrame,this,&ThreadManager::sendFrame_vehicle_in);
    connect(m_plateReaderVehicleOut,&ImageProcess::getFrame,this,&ThreadManager::sendFrame_vehicle_out);

}

ThreadManager::~ThreadManager()
{
    emit terminateAllThreads();
    delete m_camVehicleIn;
    delete m_camVehicleOut;
    delete m_plateReaderVehicleIn;
    delete m_plateReaderVehicleOut;
}

ThreadManager* ThreadManager::getInstance(ApplicationWindow* appwindow, unsigned int vehicle_in_CamIndex, unsigned int vehicle_out_CamIndex)
{
    if(!m_instance) m_instance = new ThreadManager(appwindow,vehicle_in_CamIndex,vehicle_out_CamIndex);
    return m_instance;
}

void ThreadManager::startCameraSystem()
{
    emit startThreads();
}

cv::Mat ThreadManager::getFrame_in()
{
    return m_Frame_vehicle_in;
}

cv::Mat ThreadManager::getFrame_out()
{
    return m_Frame_vehicle_out;
}

void ThreadManager::stopAllThreads()
{
    emit stopThreads();
}


void ThreadManager::terminateAllThreads()
{
    emit terminateThreads();
}

void ThreadManager::capturedFrame_vehicle_in(cv::Mat frame)
{
    m_Frame_vehicle_in = frame;
}

void ThreadManager::capturedFrame_vehicle_out(cv::Mat frame)
{
    m_Frame_vehicle_out = frame;
}

void ThreadManager::sendFrame_vehicle_in(cv::Mat* frame)
{
    *frame = m_Frame_vehicle_in;
}

void ThreadManager::sendFrame_vehicle_out(cv::Mat* frame)
{
    *frame = m_Frame_vehicle_out;
}

