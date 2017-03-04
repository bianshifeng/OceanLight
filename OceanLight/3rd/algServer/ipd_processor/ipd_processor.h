#ifndef IPD_PROCESSOR_H
#define IPD_PROCESSOR_H

#include <QThread>
#include <iostream>
#include <QVideoFrame>
#include "common/IMP_FrameQueue.h"
#include "common/imp_algo_type.h"
class IPDProcessor : public QThread
{
    Q_OBJECT
public:
    IPDProcessor();
    ~IPDProcessor();
    void set_video_resolution(int width, int height);
    void initFrameQueue();
    void push_video_frame(const QVideoFrame &videoFrame);
    void stop();

protected:
    void run();
    void setEmitIpdData(QJsonObject &dataStr);

signals:
    void sig_alg_result(const QString &algMessage);

 private:
    IMP_FrameQueue* m_frame_queue;
    volatile bool stopped;
    int videoWidth;
    int videoHeight;

    void downSize(IMAGE3_S *pstSrc, IMAGE3_S *pstDst);
    void RGBA2YUV420P(unsigned char *RgbaBuf,int nWidth,int nHeight,unsigned char *yuvBuf);

};

#endif // IPD_PROCESSOR_H
