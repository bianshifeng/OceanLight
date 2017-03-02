#ifndef IPD_PROCESSOR_H
#define IPD_PROCESSOR_H

#include <QThread>
#include <iostream>
#include <QVideoFrame>
#include "IMP_FrameQueue.h"
#include "imp_algo_type.h"
class ipd_processor : public QThread
{
    Q_OBJECT
public:
    ipd_processor();
    void setMessage(QString message);
    void stop();
    void set_frame_queue(IMP_FrameQueue* frame_queue);
    void push_frame(QImage &frame);
    void set_video_resolution(int width, int height);
protected:
    void run();
    void printMessage();
    void setEmitData(QString &dataStr);

 private:
    IMP_FrameQueue* m_frame_queue;
    QString messageStr;
    volatile bool stopped;
    int videoWidth;
    int videoHeight;
    void downSize(IMAGE3_S *pstSrc, IMAGE3_S *pstDst);
    void RGBA2YUV420P(unsigned char *RgbaBuf,int nWidth,int nHeight,unsigned char *yuvBuf);
    void setEmitIpdData(QJsonObject &dataStr);
};

#endif // IPD_PROCESSOR_H
