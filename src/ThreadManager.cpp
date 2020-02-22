#include "ThreadManager.hpp"

#include "applicationwindow.hpp"
#include "CameraVehicleIn.hpp"
#include "CameraVehicleOut.hpp"
#include "ImageProcess.hpp"

#include <QThread>

ThreadManager* ThreadManager::m_instance(0);

ThreadManager::ThreadManager(ApplicationWindow* appwindow) : m_appwindow(appwindow)
{
    m_camVehicleIn = new CameraVehicleIn(this);
    m_camVehicleOut = new CameraVehicleOut(this);
    m_plateReader = new ImageProcess(this);
    connect(this,&ThreadManager::startCamVehicleIn,m_camVehicleIn,&CameraVehicleIn::startThread);
    connect(this,&ThreadManager::stopCamVehicleIn,m_camVehicleIn,&CameraVehicleIn::stopCameraStream);
    connect(this,&ThreadManager::startCamVehicleOut,m_camVehicleOut,&CameraVehicleOut::startThread);
    connect(this,&ThreadManager::stopCamVehicleOut,m_camVehicleOut,&CameraVehicleOut::stopCameraStream);
    connect(this,&ThreadManager::readPlateNumber,m_plateReader,&ImageProcess::startThread);
    connect(this,&ThreadManager::stopImageProcessing,m_plateReader,&ImageProcess::stopThread);
}

ThreadManager::~ThreadManager()
{
    delete m_camVehicleIn;
    delete m_camVehicleOut;
    delete m_plateReader;
}

ThreadManager* ThreadManager::getInstance(ApplicationWindow* appwindow)
{
    if(!m_instance) m_instance = new ThreadManager(appwindow);
    return m_instance;
}

ApplicationWindow* ThreadManager::getAppWindow()
{
    return m_appwindow;
}


void ThreadManager::terminateAllThreads()
{
    stopCamVehicleIn();
    stopCamVehicleOut();
    stopImageProcessing();
}
