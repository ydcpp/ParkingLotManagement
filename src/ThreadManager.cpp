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
    // main window connections
    connect(m_appwindow,&ApplicationWindow::stopAllThreads,this,&ThreadManager::stopAllThreads);
    connect(m_appwindow,&ApplicationWindow::terminateAllThreads,this,&ThreadManager::terminateAllThreads);
    connect(m_appwindow,&ApplicationWindow::recognizePlate_in,this,&ThreadManager::recognizePlate_in);
    connect(m_appwindow,&ApplicationWindow::recognizePlate_out,this,&ThreadManager::recognizePlate_out);
    // incoming vehicles camera setup
    connect(m_camVehicleIn,&CameraStream::updateCameraDisplay,m_appwindow,&ApplicationWindow::drawCamInput_vehicle_in);
    connect(m_camVehicleIn,&CameraStream::cameraIsOpen,m_appwindow,&ApplicationWindow::openCameraStream_in);
    connect(m_camVehicleIn,&CameraStream::cameraIsClosed,m_appwindow,&ApplicationWindow::closeCameraStream_in);
    connect(m_camVehicleIn,&CameraStream::cameraIsClosed,m_plateReaderVehicleIn,&ImageProcess::stopThread);
    // outgoing vehicles camera setup
    connect(m_camVehicleOut,&CameraStream::updateCameraDisplay,m_appwindow,&ApplicationWindow::drawCamInput_vehicle_out);
    connect(m_camVehicleOut,&CameraStream::cameraIsOpen,m_appwindow,&ApplicationWindow::openCameraStream_out);
    connect(m_camVehicleOut,&CameraStream::cameraIsClosed,m_appwindow,&ApplicationWindow::closeCameraStream_out);
    connect(m_camVehicleOut,&CameraStream::cameraIsClosed,m_plateReaderVehicleOut,&ImageProcess::stopThread);
    // image process thread setup
    connect(m_plateReaderVehicleIn,&ImageProcess::sendPlateString,m_appwindow,&ApplicationWindow::displayLicensePlateString_vehicle_in);
    connect(m_plateReaderVehicleOut,&ImageProcess::sendPlateString,m_appwindow,&ApplicationWindow::displayLicensePlateString_vehicle_out);

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


void ThreadManager::stopAllThreads()
{
    emit stopThreads();
}


void ThreadManager::terminateAllThreads()
{
    emit terminateThreads();
}


void ThreadManager::recognizePlate_in()
{
    cv::Mat capturedFrame;
    m_camVehicleIn->getCurrentFrame(&capturedFrame);
    m_plateReaderVehicleIn->startThread(capturedFrame);
}

void ThreadManager::recognizePlate_out()
{
    cv::Mat capturedFrame;
    m_camVehicleOut->getCurrentFrame(&capturedFrame);
    m_plateReaderVehicleOut->startThread(capturedFrame);
}

