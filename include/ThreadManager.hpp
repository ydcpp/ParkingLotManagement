#ifndef THREADMANAGER_HPP
#define THREADMANAGER_HPP

#include <QObject>
#include <QCamera>
#include <QCameraViewfinder>

class CameraStream;
class ImageProcess;
class ApplicationWindow;


class ThreadManager : public QObject
{
    Q_OBJECT
public:
    static ThreadManager* getInstance(ApplicationWindow* appwindow, QCameraViewfinder* camview_in, QCameraViewfinder* camview_out);
    static void ReleaseInstance();
    void updateCameraDevice_in(QVariant device);
    void updateCameraDevice_out(QVariant device);
signals:
    void startThreads();
    void stopThreads();
    void terminateThreads();
    void plateDetected_in();
    void plateNotDetected_in();
    void plateDetected_out();
    void plateNotDetected_out();

private slots:
    void stopAllThreads();
    void terminateAllThreads();
    void recognizePlate_in();
    void recognizePlate_out();
    void onPlateFound_in();
    void onPlateNotFound_in();
    void onPlateFound_out();
    void onPlateNotFound_out();

private:
    ThreadManager(ApplicationWindow* appwindow, QCameraViewfinder* camview_in, QCameraViewfinder* camview_out);
    ~ThreadManager();

    ApplicationWindow* m_appwindow = nullptr;
    CameraStream* m_camVehicleIn = nullptr;
    CameraStream* m_camVehicleOut = nullptr;
    ImageProcess* m_plateReaderVehicleIn = nullptr;
    ImageProcess* m_plateReaderVehicleOut = nullptr;

    static ThreadManager* m_instance;
    static quint32 _refCounter;

};

#endif // THREADMANAGER_HPP
