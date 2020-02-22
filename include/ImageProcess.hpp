#ifndef IMAGEPROCESS_HPP
#define IMAGEPROCESS_HPP

#include <QThread>
#include <QImage>
#include <QPixmap>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


class ThreadManager;


class ImageProcess : public QThread
{
public:
    ImageProcess(ThreadManager* tmanager);
    ~ImageProcess() override;

    void run() override;

public slots:
    void stopThread();
    void startThread();

private:
    ThreadManager* m_tmanager;
    bool m_keepRunning = true;
};

#endif // IMAGEPROCESS_HPP
