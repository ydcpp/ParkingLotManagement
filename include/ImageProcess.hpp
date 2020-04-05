#ifndef IMAGEPROCESS_HPP
#define IMAGEPROCESS_HPP

#include <QThread>
#include <QImage>
#include <QString>


#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


class ThreadManager;
class CameraStream;

class ImageProcess : public QThread
{
    Q_OBJECT
public:
    ImageProcess(ThreadManager* tmanager, CameraStream* cam);
    ~ImageProcess() override;

    void run() override;
    void startThread(const QImage& frameToProcess);

signals:
    void sendPlateString(const QString&);

public slots:
    void stopThread();
private slots:
    void terminateThread();
    cv::Mat convertImage(QImage img, bool inCloneImageData);

private:
    ThreadManager* m_tmanager;
    CameraStream* m_camera;
    char* m_outText = nullptr;

    QImage qt_image;
    cv::Mat m_frame;

};

#endif // IMAGEPROCESS_HPP
