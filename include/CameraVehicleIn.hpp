#ifndef CAMERAVEHICLEIN_HPP
#define CAMERAVEHICLEIN_HPP

#include <QThread>
#include <QImage>
#include <QPixmap>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


class ThreadManager;

class CameraVehicleIn : public QThread
{
    Q_OBJECT

public:
    CameraVehicleIn(ThreadManager* app);

    int getFPS() const;
    void setFPS(int value);
    void run() override;

public slots:
    void stopCameraStream();
    void startThread();

signals:
    void updateCameraDisplay_vehicle_in(QPixmap);

private:
    ThreadManager* m_tmanager;
    cv::VideoCapture m_vidcap;

    int m_MaxFPS = 50;
    bool m_keepStreaming = true;

    cv::Mat frame;
    QImage qt_image;

};

#endif // CAMERAVEHICLEIN_HPP
