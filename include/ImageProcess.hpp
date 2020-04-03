#ifndef IMAGEPROCESS_HPP
#define IMAGEPROCESS_HPP

#include <QThread>
#include <QImage>
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
    void startThread(cv::Mat& frameToProcess);

signals:
    void sendPlateString(const QString&);

public slots:
    void stopThread();
private slots:
    void terminateThread();

private:
    ThreadManager* m_tmanager;
    char* m_outText = nullptr;

    QImage qt_image;
    cv::Mat m_frame;

};

#endif // IMAGEPROCESS_HPP
