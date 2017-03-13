#ifndef PFR_PROCESSOR_H
#define PFR_PROCESSOR_H

#include <QThread>
#include <iostream>
#include <QVideoFrame>
#include "IMP_StringQueue.h"
#include "common/imp_algo_type.h"
class PFRProcessor : public QThread
{
    Q_OBJECT
public:
    PFRProcessor();
    ~PFRProcessor();
    void set_video_resolution(int width, int height);
    void initFrameQueue();
    void push_frame(QString &file_path, int recOrReg, QString &name);
    void stop();
    void startProcessor();
    void set_frame_queue(IMP_StringQueue* queue);

protected:
    void run();

 private:
    IMP_StringQueue* m_queue;
    QString messageStr;
    volatile bool stopped;
    int videoWidth;
    int videoHeight;
    void downSize(IMAGE3_S *pstSrc, IMAGE3_S *pstDst);
    void RGBA2YUV420P(unsigned char *RgbaBuf,int nWidth,int nHeight,unsigned char *yuvBuf);
    void RGBA2YUV420P_QVideoFrame(unsigned char *RgbaBuf,int nWidth,int nHeight,unsigned char *yuvBuf);
    void setEmitPfrData(QString &dataStr);

};

#endif // PFR_PROCESSOR_H
