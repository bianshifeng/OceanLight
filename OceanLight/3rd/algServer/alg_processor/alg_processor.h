#ifndef ALG_PROCESSOR_H
#define ALG_PROCESSOR_H

#include <QThread>
#include <QVideoFrame>
#include "common/IMP_FrameQueue.h"
#include "common/imp_algo_type.h"
#include "alg_server.h"

class QImage;
class AlgProcessor : public QThread
{
    Q_OBJECT
public:
    explicit AlgProcessor();
    ~AlgProcessor();
    void initFrameQueue(const int width, const int height);
    void push_video_frame(const QVideoFrame &videoFrame);
    void push_video_image(const QImage &videoImage);
    void stop();
    void stopProcessor();
    void resetProcessor();
    void startProcessor();

    QImage imageFromVideoFrame(const QVideoFrame& buffer) const;

    QImage imageFromVideoFrame_convert(const QVideoFrame& buffer) const;

    QString saveImageFrameMetaData(const QString &saveName,unsigned char *ptrFrameBuff,int nWidth,int nHeight,QImage::Format format) const;

    bool is_processor_init;


signals:

public slots:


protected:
   IMP_FrameQueue* m_frame_queue;
   volatile bool stopped;
   int videoWidth;
   int videoHeight;

   AlgServer::AlgType m_alg_type;

   void downSize(IMAGE3_S *pstSrc, IMAGE3_S *pstDst);
   virtual void RGBA2YUV420P(unsigned char *RgbaBuf,int nWidth,int nHeight,unsigned char *yuvBuf);
   virtual void RGBA2YUV420P_QVideoFrame(unsigned char *RgbaBuf,int nWidth,int nHeight,unsigned char *yuvBuf);

};

#endif // ALG_PROCESSOR_H
