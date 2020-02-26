#ifndef IMAGEPROCESS_HPP
#define IMAGEPROCESS_HPP

#include <QThread>
#include <QImage>
#include <QPixmap>
#include <QString>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


class ThreadManager;


class ImageProcess : public QThread
{
    Q_OBJECT
public:
    ImageProcess(ThreadManager* tmanager);
    ~ImageProcess() override;

    void run() override;

signals:
    void sendPlateString(QString);
    void getFrame(cv::Mat*);

private slots:
    void stopThread();
    void startThread();

private:
    ThreadManager* m_tmanager;
    bool m_keepRunning = true;

    QImage qt_image;
    cv::Mat m_frame;
};

#endif // IMAGEPROCESS_HPP
