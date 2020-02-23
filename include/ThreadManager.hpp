#ifndef THREADMANAGER_HPP
#define THREADMANAGER_HPP

#include <QObject>


#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class CameraStream;
class ImageProcess;
class ApplicationWindow;


class ThreadManager : public QObject
{
    Q_OBJECT
public:

    ~ThreadManager();
    static ThreadManager* getInstance(ApplicationWindow* appwindow, unsigned int vehicle_in_CamIndex, unsigned int vehicle_out_CamIndex);
    ApplicationWindow* getAppWindow();


public slots:
    void terminateAllThreads();
    void capturedFrame_vehicle_in(cv::Mat);
    void capturedFrame_vehicle_out(cv::Mat);
    cv::Mat sendFrame_vehicle_in();
    cv::Mat sendFrame_vehicle_out();

signals:
    //cam stream vehicle in thread
    void startCamVehicleIn();
    void stopCamVehicleIn();

    // cam stream vehicle out thread
    void startCamVehicleOut();
    void stopCamVehicleOut();

    // license plate reader thread
    void readPlateVehicleIn();
    void readPlateVehicleOut();
    void stopImageProcessingIn();
    void stopImageProcessingOut();

private:
    ThreadManager(ApplicationWindow* appwindow, unsigned int vehicle_in_CamIndex, unsigned int vehicle_out_CamIndex);

    ApplicationWindow* m_appwindow = nullptr;
    CameraStream* m_camVehicleIn = nullptr;
    CameraStream* m_camVehicleOut = nullptr;
    ImageProcess* m_plateReaderVehicleIn = nullptr;
    ImageProcess* m_plateReaderVehicleOut = nullptr;
    static ThreadManager* m_instance;

    cv::Mat m_Frame_vehicle_in;
    cv::Mat m_Frame_vehicle_out;
};

#endif // THREADMANAGER_HPP
