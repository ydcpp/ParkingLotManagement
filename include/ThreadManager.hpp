#ifndef THREADMANAGER_HPP
#define THREADMANAGER_HPP

#include <QObject>
#include <QVector>


class CameraVehicleIn;
class CameraVehicleOut;
class ImageProcess;
class ApplicationWindow;

class ThreadManager : public QObject
{
    Q_OBJECT
public:

    ~ThreadManager();
    static ThreadManager* getInstance(ApplicationWindow* appwindow);

    ApplicationWindow* getAppWindow();


public slots:
    void terminateAllThreads();

signals:
    //cam stream vehicle in thread
    void startCamVehicleIn();
    void stopCamVehicleIn();

    // cam stream vehicle out thread
    void startCamVehicleOut();
    void stopCamVehicleOut();

    // license plate reader thread
    void readPlateNumber();
    void stopImageProcessing();

private:
    ThreadManager(ApplicationWindow* appwindow);

    ApplicationWindow* m_appwindow = nullptr;
    CameraVehicleIn* m_camVehicleIn = nullptr;
    CameraVehicleOut* m_camVehicleOut = nullptr;
    ImageProcess* m_plateReader = nullptr;
    static ThreadManager* m_instance;

};

#endif // THREADMANAGER_HPP
