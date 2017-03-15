#include "alg_processor.h"
#include <QImage>
#include <QApplication>
#include <QDebug>

AlgProcessor::AlgProcessor():
    m_frame_queue(Q_NULLPTR),
    videoWidth(DEFAULT_MALLOC_WIDTH),
    videoHeight(DEFAULT_MALLOC_WIDTH),
    stopped(false),
    is_processor_init(false)
{
    m_frame_queue = new IMP_FrameQueue();
    moveToThread(this);
}

AlgProcessor::~AlgProcessor()
{
    stopped = false;
    if(m_frame_queue){
        delete m_frame_queue;
    }

}

void AlgProcessor::initFrameQueue(const int width, const int height)
{
    this->videoWidth = width;
    this->videoHeight = height;
    m_frame_queue->setMallocWidth(this->videoWidth);
    m_frame_queue->setMallocWidth(this->videoHeight);
    m_frame_queue->InitFrameQueue();
    this->is_processor_init = true;
}

void AlgProcessor::push_video_frame(const QVideoFrame &videoFrame)
{
    if(!is_processor_init) return;


    IMP_PicOutFrame *t_free_frame = m_frame_queue->GetFrameAddr();
    if(!t_free_frame) return;


    QVideoFrame t_frame(videoFrame);
    t_frame.map(QAbstractVideoBuffer::ReadOnly);

    memcpy(t_free_frame->pu8D1,t_frame.bits(),t_frame.width()*t_frame.height()*4);
    t_free_frame->nWidth = t_frame.width();
    t_free_frame->nHeight = t_frame.height();

    t_frame.unmap();

}

void AlgProcessor::stop()
{
    this->stopped = true;
    if(m_frame_queue){
        m_frame_queue->ClearQueue();
    }
}

void AlgProcessor::startProcessor()
{
    if(!is_processor_init) return;
    this->stopped = false;
    this->start();
}

QImage AlgProcessor::imageFromVideoFrame(const QVideoFrame &buffer) const
{
    QImage img;
    QVideoFrame frame(buffer);  // make a copy we can call map (non-const) on
    frame.map(QAbstractVideoBuffer::ReadOnly);


    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(
                frame.pixelFormat());
    // BUT the frame.pixelFormat() is QVideoFrame::Format_Jpeg, and this is
    // mapped to QImage::Format_Invalid by
    // QVideoFrame::imageFormatFromPixelFormat
    if (imageFormat != QImage::Format_Invalid) {
        img = QImage(frame.bits(),
                     frame.width(),
                     frame.height(),
                     // frame.bytesPerLine(),
                     imageFormat);



        //img.save(QString::number(c_alg_image_index).append(".png"));
    } else {
        // e.g. JPEG
        int nbytes = frame.mappedBytes();
        img = QImage::fromData(frame.bits(), nbytes);
        //img.save("456.png");
    }



    frame.unmap();
    return img;

}

QString AlgProcessor::saveImageFrameMetaData(const QString &saveName, unsigned char *ptrFrameBuff, int nWidth, int nHeight, QImage::Format format) const
{
    QString abs_path = qApp->applicationDirPath();
    QImage t_face_image(ptrFrameBuff,nWidth,nHeight,format);
    abs_path = abs_path.append("/").append(saveName).append(".jpg");
    t_face_image.save(abs_path,"JPG");

    return abs_path;
}

void AlgProcessor::downSize(IMAGE3_S *pstSrc, IMAGE3_S *pstDst)
{
    IMP_S32 w_src = 0, h_src = 0, w_dst = 0, h_dst = 0;
    IMP_U8 *pYsrc = NULL, *pUsrc = NULL, *pVsrc = NULL, *pYdst = NULL, *pUdst = NULL, *pVdst = NULL;

    IMP_S32 i = 0, j = 0, x = 0, y = 0;

    w_src = pstSrc->s32W;
    h_src = pstSrc->s32H;

    w_dst = pstDst->s32W;
    h_dst = pstDst->s32H;

    IMP_FLOAT fSampleItvlW = (IMP_FLOAT)w_src / w_dst;
    IMP_FLOAT fSampleItvlH = (IMP_FLOAT)h_src / h_dst;

    IMP_FLOAT fCoorW = 0.0, fCoorH = 0.0;
    IMP_S32 *as32IdxW = (IMP_S32 *)malloc(w_dst * sizeof(IMP_S32));
    IMP_S32 *as32IdxH = (IMP_S32 *)malloc(h_dst * sizeof(IMP_S32));

    for (i=0; i<w_dst; ++i)
    {
        as32IdxW[i] = (IMP_S32)(fCoorW + 0.5);
        fCoorW += fSampleItvlW;
        //printf("%d ", as32IdxW[i]);
    }

    for (i=0; i<h_dst; ++i)
    {
        as32IdxH[i] = (IMP_S32)(fCoorH + 0.5);
        fCoorH += fSampleItvlH;
    }
    //yuv420
    //if(pstSrc->enFormat == IMAGE_FORMAT_IMP_YUV420)
    if (1)
    {
        pstDst->enFormat = IMAGE_FORMAT_IMP_YUV420;

        for(j=0; j<h_dst; ++j)
        {
            y = as32IdxH[j];
            pYsrc = pstSrc->pu8D1 + y*w_src;

            pYdst = pstDst->pu8D1 + j*w_dst;

            for(i=0; i<w_dst; ++i)
            {
                x = as32IdxW[i];
                *(pYdst + i) = *(pYsrc + x);
            }
        }

        for (j=0; j<h_dst; j+=2)
        {
            y = as32IdxH[j];

            pUsrc = pstSrc->pu8D2 + (y>>1) * (w_src>>1);
            pVsrc = pstSrc->pu8D3 + (y>>1) * (w_src>>1);

            pUdst = pstDst->pu8D2 + (j>>1) * (w_dst>>1);
            pVdst = pstDst->pu8D3 + (j>>1) * (w_dst>>1);

            for (i=0; i<w_dst; i+=2)
            {
                x = as32IdxW[i];

                *(pUdst + (i>>1)) = *(pUsrc + (x>>1));
                *(pVdst + (i>>1)) = *(pVsrc + (x>>1));
            }
        }
    }

    free(as32IdxH);
    as32IdxH = NULL;

    free(as32IdxW);
    as32IdxW = NULL;

}

void AlgProcessor::RGBA2YUV420P(unsigned char *RgbaBuf, int nWidth, int nHeight, unsigned char *yuvBuf)
{
    int i,j,pos;
    unsigned char*bufY,*bufU,*bufV,*bufRGBA,*bufYuv;
    unsigned char y,u,v,r,g,b,a,testu,testv;
    unsigned int ylen = nWidth * nHeight;
    unsigned int ulen = (nWidth * nHeight)/4;
    unsigned int vlen = (nWidth * nHeight)/4;
    bufY = yuvBuf;
    bufV = yuvBuf + nWidth * nHeight;
    bufU = bufV + (nWidth * nHeight* 1/4);



    for (j = 0; j<nHeight;j++)
    {
        bufRGBA = RgbaBuf + nWidth * j * 4 ;
        for (i = 0;i<nWidth;i++)
        {
            pos = nWidth * i + j;

            r = *(bufRGBA++);
            g = *(bufRGBA++);
            b = *(bufRGBA++);
            a = *(bufRGBA++);

            y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;
            u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;
            v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;
            *(bufY++) = max( 0, min((int)y, 255 ));

            if (j%2==0&&i%2 ==0)
            {
                if (u>255)
                {
                    u =	255;
                }
                if (u<0)
                {
                    u = 0;
                }
                *(bufU++) =u;
            }
            else
            {
                if (i%2==0)
                {
                    if (v>255)
                    {
                        v = 255;
                    }
                    if (v<0)
                    {
                        v = 0;
                    }
                    *(bufV++) =v;
                }
            }
        }
    }

}

void AlgProcessor::RGBA2YUV420P_QVideoFrame(unsigned char *RgbaBuf, int nWidth, int nHeight, unsigned char *yuvBuf)
{

    int i,j,pos;
    unsigned char*bufY,*bufU,*bufV,*bufRGBA,*bufYuv;
    unsigned char y,u,v,r,g,b,a,testu,testv;
    unsigned int ylen = nWidth * nHeight;
    unsigned int ulen = (nWidth * nHeight)/4;
    unsigned int vlen = (nWidth * nHeight)/4;
    bufY = yuvBuf + nWidth * nHeight - 1;
    bufV = yuvBuf + nWidth * nHeight + (nWidth * nHeight* 1/4) - 1;
    bufU = yuvBuf + (nWidth * nHeight* 3/2) - 1;

    for (j = 0; j<nHeight;j++)
    {
        bufRGBA = RgbaBuf + nWidth * j * 4 ;
        for (i = 0;i<nWidth;i++)
        {
            pos = nWidth * i + j;

            r = *(bufRGBA++);
            g = *(bufRGBA++);
            b = *(bufRGBA++);
            a = *(bufRGBA++);

            y = (unsigned char)( ( 66 * r + 129 * g +  25 * b + 128) >> 8) + 16  ;
            u = (unsigned char)( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128 ;
            v = (unsigned char)( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128 ;
            *(bufY--) = max( 0, min(y, 255 ));

            if (j%2==0&&i%2 ==0)
            {
                if (u>255)
                {
                    u =	255;
                }
                if (u<0)
                {
                    u = 0;
                }
                *(bufU--) =u;
            }
            else
            {
                if (i%2==0)
                {
                    if (v>255)
                    {
                        v = 255;
                    }
                    if (v<0)
                    {
                        v = 0;
                    }
                    *(bufV--) =v;
                }
            }
        }
    }

}
