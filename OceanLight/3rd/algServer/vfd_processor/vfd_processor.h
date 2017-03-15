#ifndef VFD_PROCESSOR_H
#define VFD_PROCESSOR_H

#include <QThread>
#include <iostream>
#include <QVideoFrame>
#include "common/IMP_FrameQueue.h"
#include "common/imp_algo_type.h"

#include "imp_vfd_api.h"
class VFDProcessor : public QThread
{
    Q_OBJECT
public:
    VFDProcessor();
    ~VFDProcessor();
    void set_video_resolution(int width, int height);
    void initFrameQueue();
    void push_video_frame(const QVideoFrame &videoFrame);
    void stop();
    void startProcessor();

protected:
    void run();
    void setEmitVfdData(QJsonObject &dataStr);

signals:
    void sig_alg_result(const QString &algMessage);

private:
    IMP_FrameQueue* m_frame_queue;
    volatile bool stopped;
    int videoWidth;
    int videoHeight;

    void downSize(IMAGE3_S *pstSrc, IMAGE3_S *pstDst);
    void RGBA2YUV420P(unsigned char *RgbaBuf,int nWidth,int nHeight,unsigned char *yuvBuf);
    void RGBA2YUV420P_QVideoFrame(unsigned char *RgbaBuf,int nWidth,int nHeight,unsigned char *yuvBuf);


    QString _getPicName(IMP_VFD_RESULT_S &stResult,int i) const;
    QString _saveFacePic(const QString imageName,uchar *tmpM, int faceW, int faceH) const;
    QString _getBigPicName(int tmpSizeTimes, IMP_VFD_RESULT_S &stResult,int i,int nFrameWidth)const;
    QString _saveBigPic(const QString imageName,uchar *imageSrc,int imageW,int imageH) const;

};

#endif // VFD_PROCESSOR_H
