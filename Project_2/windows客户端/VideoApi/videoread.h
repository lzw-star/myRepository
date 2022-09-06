#ifndef VIDEOREAD_H
#define VIDEOREAD_H

#include <QObject>
#include <QImage>
#include<QTimer>
#include"common.h"

#include"threadworker.h"
//图片的宽高
#define IMAGE_WIDTH (320)
#define IMAGE_HEIGHT (240)



class VideoWorker;
class VideoRead : public QObject
{
    Q_OBJECT
public:
    explicit VideoRead(QObject *parent = nullptr);
    ~VideoRead();
signals:
    void SIG_sendVideoFrame(QImage img);
public slots:
    void slot_getVideoFrame();
    void slot_openVideo();
    void slot_closeVideo();
private:
    QTimer *m_timer;

    //opencv获取图片的对象
    cv::VideoCapture cap;

    QSharedPointer<VideoWorker> m_pVideoWorker;
};

class VideoWorker: public ThreadWorker
{
    Q_OBJECT
public slots:
    void slot_setInfo(VideoRead * p){
        m_pVideoRead = p;
    }
    //定时器到时, 执行
    void slot_dowork() {
        m_pVideoRead->slot_getVideoFrame();
    }

private:
    VideoRead * m_pVideoRead;
};

#endif // VIDEOREAD_H
