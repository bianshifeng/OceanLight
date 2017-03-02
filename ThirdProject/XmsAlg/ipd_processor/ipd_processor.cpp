#include <QDebug>
#include <QJsonObject>
#include "ipd_processor.h"
#include "imp_ipd_api.h"
using namespace std;
ipd_processor::ipd_processor()
{
    stopped = false;
}

void ipd_processor::set_video_resolution(int width, int height)
{
    videoWidth = width;
    videoHeight = height;
}

void ipd_processor::downSize(IMAGE3_S *pstSrc, IMAGE3_S *pstDst)
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

void ipd_processor::RGBA2YUV420P(unsigned char *RgbaBuf,int nWidth,int nHeight,unsigned char *yuvBuf)
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
            *(bufY++) = std::max( 0, std::min((int)y, 255));

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

void ipd_processor::run()
{
    IMP_S32 width = 320;
    IMP_S32 height = 180;
    IMP_HANDLE handle;
    IMP_IPD_Create(width, height, &handle);
    IMP_IPD_Result_S stResult;
    IMP_IPD_Para_S stParas;
    memset(&stResult,0,sizeof(IMP_IPD_Result_S));
    memset(&stParas,0,sizeof(IMP_IPD_Para_S));

    IMAGE3_S image;
    image.s32W = width;
    image.s32H = height;
    image.pu8D1 = (IMP_U8*)malloc(sizeof(IMP_U8)*width*height*1.5);
    image.pu8D2 = image.pu8D1 + width*height;
    image.pu8D3 = image.pu8D2 + width*height/4;


    IMAGE3_S tmpImage;
    tmpImage.s32W = videoWidth;
    tmpImage.s32H = videoHeight;
    tmpImage.pu8D1 = (IMP_U8*)malloc(sizeof(IMP_U8)*videoWidth*videoHeight*1.5);
    tmpImage.pu8D2 = tmpImage.pu8D1 + videoWidth*videoHeight;
    tmpImage.pu8D3 = tmpImage.pu8D2 + videoWidth*videoHeight/4;

    IMP_PicOutFrame *frame = NULL;

    stParas.enSensity = IMP_IPD_SENS_NORMAL;
    IMP_IPD_Config(handle,&stParas);

    int frame_count = 0,ipd_count = 0, isWarning = 0;

    while(!stopped)
    {
        m_frame_queue->PeekFrame(&frame);
        if(NULL == frame)
        {
            usleep(100000);
            continue;
        }
        IMP_U8 *tmpMem = (IMP_U8*)malloc(sizeof(IMP_U8)*frame->nWidth*frame->nHeight*1.5);
        this->RGBA2YUV420P(frame->pu8D1,frame->nWidth,frame->nHeight,tmpImage.pu8D1);
        this->downSize(&tmpImage,&image);
        //QVideoFrame *tmp = new QVideoFrame();
        //QVideoFrame::
        IMP_IPD_Process(handle,&image,NULL,&stResult);
        frame_count ++;
        if(stResult.s32TgtNum > 0)ipd_count++;
        if(frame_count%10 == 0)
        {
            if(ipd_count > 7 && isWarning == 0)
            {
                QJsonObject json;
                json.insert("name",QString("IPD"));
                json.insert("status",QString("warning"));
                this->setEmitIpdData(json);
                isWarning = 1;
            }
            if(ipd_count < 7 && isWarning == 1)
            {
                QJsonObject json;
                json.insert("name",QString("IPD"));
                json.insert("status",QString("clear"));
                this->setEmitIpdData(json);
                isWarning == 0;
            }
        }
        m_frame_queue->RemoveFrame();
        usleep(100000);
    }
    IMP_IPD_Release(handle);
    free(image.pu8D1);
    free(tmpImage.pu8D1);
    stopped = false;
}

void ipd_processor::stop()
{
    stopped = true;
}

void ipd_processor::setMessage(QString message)
{
    messageStr = message;
}

void ipd_processor::printMessage()
{
    qDebug()<<messageStr;
    sleep(1);
}

void ipd_processor::setEmitIpdData(QJsonObject &dataStr)
{
    qDebug() << dataStr;
}
void ipd_processor::set_frame_queue(IMP_FrameQueue* frame_queue)
{
    m_frame_queue = frame_queue;
}
void ipd_processor::push_frame(QImage &frame)
{
    IMP_PicOutFrame *free_node = m_frame_queue->GetFrameAddr();
    if(!free_node) return;
    memcpy(free_node->pu8D1, frame.bits(), frame.width() * frame.height() * 4);
    free_node->nWidth = frame.width();
    free_node->nHeight = frame.height();
}
