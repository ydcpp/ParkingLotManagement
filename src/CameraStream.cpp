#include "CameraStream.hpp"
#include "ThreadManager.hpp"
#include "settingspanel.hpp"

#include <QMediaService>
#include <QMediaMetaData>
#include <QBuffer>

#include <QDebug>

Q_DECLARE_METATYPE(QCameraInfo)

CameraStream::CameraStream(ThreadManager* tmanager,QCameraViewfinder* camviewfinder)
    : m_tmanager(tmanager), m_camviewfinder(camviewfinder), m_currentCamInfo(QCameraInfo::defaultCamera())
{
    connect(m_tmanager,&ThreadManager::startThreads,this,&CameraStream::startCamera);
    connect(m_tmanager,&ThreadManager::stopThreads,this,&CameraStream::stopCamera);
}

CameraStream::~CameraStream()
{
}


void CameraStream::stopCamera()
{
    m_camera->stop();
    emit cameraIsClosed();
}

void CameraStream::startCamera()
{
    setCamera(m_currentCamInfo);
}

void CameraStream::updateCameraDevice(QVariant camdata)
{
    setCamera(qvariant_cast<QCameraInfo>(camdata));
}

void CameraStream::setCamera(const QCameraInfo &cameraInfo)
{
    if(!m_camera.isNull()){
        if(m_camera->LoadedState == QCamera::LoadedState) m_camera->unload();
        stopCamera();
    }
    if(cameraInfo.isNull()) return;
    m_currentCamInfo = cameraInfo;
    m_camera.reset(new QCamera(m_currentCamInfo));
    connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &CameraStream::displayCameraError);
    m_camera->setViewfinder(m_camviewfinder);
    m_camera->setCaptureMode(QCamera::CaptureStillImage);
    m_capture.reset(new QCameraImageCapture(m_camera.data()));
    connect(m_capture.data(), &QCameraImageCapture::imageCaptured, [=] (int, const QImage& img) {
        QByteArray buf;
        QBuffer buffer(&buf);
        buffer.open(QIODevice::ReadWrite);
        img.save(&buffer, "TIFF");
        qt_image = img;
    });
    m_camera->load();
    m_camera->start();
    if(m_camera->state() == QCamera::ActiveState) emit cameraIsOpen();
}

void CameraStream::displayCameraError()
{
    qDebug() << "Camera:" << m_camera->errorString();
}

void CameraStream::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    qDebug() << "Image Capture Error:" << errorString;
}

void CameraStream::onRequestMediaObject(QCamera* obj)
{
    obj = m_camera.data();
}

QImage CameraStream::captureImage()
{
    if(m_capture.isNull()) return QImage();
    m_capture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    m_camera->searchAndLock();
    m_capture->capture();
    m_camera->unlock();
    return qt_image;
}


