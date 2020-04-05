#include "ThreadManager.hpp"
#include "CameraStream.hpp"
#include "ImageProcess.hpp"
#include "applicationwindow.hpp"
#include "settingspanel.hpp"


ThreadManager* ThreadManager::m_instance(0);
quint32 ThreadManager::_refCounter = 0;

ThreadManager::ThreadManager(ApplicationWindow* appwindow, QCameraViewfinder* camview_in, QCameraViewfinder* camview_out)
    : m_appwindow(appwindow)
{
    m_camVehicleIn = new CameraStream(this, camview_in);
    m_camVehicleOut = new CameraStream(this, camview_out);
    m_plateReaderVehicleIn = new ImageProcess(this,m_camVehicleIn);
    m_plateReaderVehicleOut = new ImageProcess(this,m_camVehicleOut);
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

ThreadManager* ThreadManager::getInstance(ApplicationWindow* appwindow, QCameraViewfinder* camview_in, QCameraViewfinder* camview_out)
{
    if(!m_instance) m_instance = new ThreadManager(appwindow,camview_in,camview_out);
    _refCounter++;
    return m_instance;
}

void ThreadManager::ReleaseInstance()
{
    if(_refCounter == 0) return;
    _refCounter--;
    if(_refCounter == 0 && m_instance != nullptr){
        delete m_instance;
        m_instance = nullptr;
    }
}

void ThreadManager::updateCameraDevice_in(QVariant device)
{
    m_camVehicleIn->updateCameraDevice(device);
}

void ThreadManager::updateCameraDevice_out(QVariant device)
{
    m_camVehicleOut->updateCameraDevice(device);
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
    m_plateReaderVehicleIn->startThread(m_camVehicleIn->captureImage());
    /*
    cv::Mat capturedFrame;
    m_camVehicleIn->getCurrentFrame(&capturedFrame);
    m_plateReaderVehicleIn->startThread(capturedFrame);
    */
}

void ThreadManager::recognizePlate_out()
{
    m_plateReaderVehicleOut->startThread(m_camVehicleOut->captureImage());
    /*
    cv::Mat capturedFrame;
    m_camVehicleOut->getCurrentFrame(&capturedFrame);
    m_plateReaderVehicleOut->startThread(capturedFrame);
    */
}

