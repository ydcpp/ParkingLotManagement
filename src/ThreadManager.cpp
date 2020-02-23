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
    connect(m_appwindow,&ApplicationWindow::terminateAllThreads,this,&ThreadManager::terminateAllThreads);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    // incoming vehicles camera setup
    connect(this,&ThreadManager::startCamVehicleIn,m_camVehicleIn,&CameraStream::startThread);
    connect(this,&ThreadManager::stopCamVehicleIn,m_camVehicleIn,&CameraStream::stopCameraStream);
    connect(m_camVehicleIn,&CameraStream::updateCameraDisplay,m_appwindow,&ApplicationWindow::drawCamInput_vehicle_in);
    connect(m_camVehicleIn,&CameraStream::captureLicensePlate,this,&ThreadManager::capturedFrame_vehicle_in);
    connect(m_camVehicleIn,&CameraStream::updateCamStatusText,m_appwindow,&ApplicationWindow::changeCamera_in_statusText);
    // outgoing vehicles camera setup
    connect(this,&ThreadManager::startCamVehicleOut,m_camVehicleOut,&CameraStream::startThread);
    connect(this,&ThreadManager::stopCamVehicleOut,m_camVehicleOut,&CameraStream::stopCameraStream);
    connect(m_camVehicleOut,&CameraStream::updateCameraDisplay,m_appwindow,&ApplicationWindow::drawCamInput_vehicle_out);
    connect(m_camVehicleOut,&CameraStream::captureLicensePlate,this,&ThreadManager::capturedFrame_vehicle_out);
    connect(m_camVehicleOut,&CameraStream::updateCamStatusText,m_appwindow,&ApplicationWindow::changeCamera_out_statusText);
    // image process thread setup
    connect(this,&ThreadManager::readPlateVehicleIn,m_plateReaderVehicleIn,&ImageProcess::startThread);
    connect(this,&ThreadManager::stopImageProcessingIn,m_plateReaderVehicleIn,&ImageProcess::stopThread);
    connect(this,&ThreadManager::readPlateVehicleOut,m_plateReaderVehicleOut,&ImageProcess::startThread);
    connect(this,&ThreadManager::stopImageProcessingOut,m_plateReaderVehicleOut,&ImageProcess::stopThread);
    connect(m_plateReaderVehicleIn,&ImageProcess::sendPlateString,m_appwindow,&ApplicationWindow::displayLicensePlateString_vehicle_in);
    connect(m_plateReaderVehicleOut,&ImageProcess::sendPlateString,m_appwindow,&ApplicationWindow::displayLicensePlateString_vehicle_out);
    connect(m_plateReaderVehicleIn,&ImageProcess::getFrame,this,&ThreadManager::sendFrame_vehicle_in);
    connect(m_plateReaderVehicleOut,&ImageProcess::getFrame,this,&ThreadManager::sendFrame_vehicle_out);
}

ThreadManager::~ThreadManager()
{
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

ApplicationWindow* ThreadManager::getAppWindow()
{
    return m_appwindow;
}

void ThreadManager::startCameraSystem()
{
    emit startCamVehicleIn();
    emit startCamVehicleOut();
    emit readPlateVehicleIn();
    emit readPlateVehicleOut();
}


void ThreadManager::terminateAllThreads()
{
    emit stopCamVehicleIn();
    emit stopCamVehicleOut();
    emit stopImageProcessingIn();
    emit stopImageProcessingOut();
}

void ThreadManager::capturedFrame_vehicle_in(cv::Mat frame)
{
    m_Frame_vehicle_in = frame;
}

void ThreadManager::capturedFrame_vehicle_out(cv::Mat frame)
{
    m_Frame_vehicle_out = frame;
}

cv::Mat ThreadManager::sendFrame_vehicle_in()
{
    return m_Frame_vehicle_in;
}

cv::Mat ThreadManager::sendFrame_vehicle_out()
{
    return m_Frame_vehicle_out;
}

