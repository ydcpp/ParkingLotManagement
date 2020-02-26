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
    void startCameraSystem();
    cv::Mat getFrame_in();
    cv::Mat getFrame_out();

signals:
    //cam stream vehicle in thread
    void startCameraStream();
    void stopCameraStream();

    // license plate reader thread
    void readPlateVehicle();
    void stopImageProcessing();

private slots:
    void terminateAllThreads();
    void capturedFrame_vehicle_in(cv::Mat);
    void capturedFrame_vehicle_out(cv::Mat);
    void sendFrame_vehicle_in(cv::Mat*);
    void sendFrame_vehicle_out(cv::Mat*);



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
