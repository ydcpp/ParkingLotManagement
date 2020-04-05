#ifndef CAMERASTREAM_HPP
#define CAMERASTREAM_HPP

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QScopedPointer>


class ThreadManager;

class CameraStream : public QObject
{
    Q_OBJECT

public:
    CameraStream(ThreadManager* app, QCameraViewfinder* camviewfinder);
    ~CameraStream();

    void updateCameraDevice(QVariant camdata);
    QImage captureImage();

signals:
    void updateCameraDisplay(QPixmap);
    void cameraIsClosed();
    void cameraIsOpen();

private slots:
    void stopCamera();
    void startCamera();
    void setCamera(const QCameraInfo& cameraInfo);
    void displayCameraError();
    void displayCaptureError(int, QCameraImageCapture::Error, const QString &errorString);
    void onRequestMediaObject(QCamera* obj);

private:
    ThreadManager* m_tmanager;

    QImage qt_image;
    QCameraViewfinder* m_camviewfinder = nullptr;
    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QCameraImageCapture> m_capture;
    QCameraInfo m_currentCamInfo;
};

#endif // CAMERASTREAM_HPP
