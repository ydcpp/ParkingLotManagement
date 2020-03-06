#ifndef IMAGEPROCESS_HPP
#define IMAGEPROCESS_HPP

#include <QThread>
#include <QImage>
#include <QPixmap>
#include <QString>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

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
    void sendPlateString(QString);

public slots:
    void stopThread();
private slots:
    void terminateThread();

private:
    ThreadManager* m_tmanager;
    tesseract::TessBaseAPI* m_tessapi = nullptr;
    char* m_outText = nullptr;
    Pix* m_image = nullptr;

    QImage qt_image;
    cv::Mat m_frame;
};

#endif // IMAGEPROCESS_HPP
