﻿#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <iostream>
#include <QImage>
#include <QApplication>
#include "vfd_processor.h"

using namespace std;

static int RESULT_COUNT = 0;

typedef struct face_path
{
    int ID;
    QString path;
    int isQA;
    int isUsed;
}FACEPATH;

VFDProcessor::VFDProcessor():
    m_frame_queue(Q_NULLPTR),
    videoWidth(DEFAULT_MALLOC_WIDTH),
    videoHeight(DEFAULT_MALLOC_WIDTH),
    stopped(false),
    is_processor_init(false)
{
    m_frame_queue = new IMP_FrameQueue();
    moveToThread(this);
}

VFDProcessor::~VFDProcessor()
{
    qDebug() << "~VFDProcessor()";
    stopped = true;
    if(m_frame_queue){
        delete m_frame_queue;
    }

}


void VFDProcessor::initFrameQueue(const int width, const int height)
{
    videoWidth = width;
    videoHeight = height;

    m_frame_queue->ClearQueue();
    m_frame_queue->setMallocWidth(this->videoWidth);
    m_frame_queue->setMallocWidth(this->videoHeight);
    m_frame_queue->InitFrameQueue();
    this->is_processor_init = true;

}

void VFDProcessor::push_video_frame(const QVideoFrame &videoFrame)
{
    IMP_PicOutFrame *t_free_frame = m_frame_queue->GetFrameAddr();
    if(!t_free_frame) return;


    QVideoFrame t_frame(videoFrame);
    t_frame.map(QAbstractVideoBuffer::ReadOnly);

    memcpy(t_free_frame->pu8D1,t_frame.bits(),t_frame.width()*t_frame.height()*4);
    t_free_frame->nWidth = t_frame.width();
    t_free_frame->nHeight = t_frame.height();

    t_frame.unmap();

}


void VFDProcessor::run()
{
    IMP_S32 width = this->videoWidth;
    IMP_S32 height = this->videoHeight;

    qDebug() << QString::number(width);
    qDebug() << QString::number(height);
    IMP_HANDLE handle;
    handle = IMP_VFD_Create(width, height);
    IMP_VFD_RESULT_S stResult;
    IMP_VFD_PARA_S stParas;
    memset(&stResult,0,sizeof(IMP_VFD_RESULT_S));
    memset(&stParas,0,sizeof(IMP_VFD_PARA_S));

    IMAGE3_S image;
    image.s32W = width;
    image.s32H = height;
    image.pu8D1 = (IMP_U8*)malloc(sizeof(IMP_U8)*width*height*1.5);
    image.pu8D2 = image.pu8D1 + width*height;
    image.pu8D3 = image.pu8D2 + width*height/4;
    image.enFormat = IMAGE_FORMAT_IMP_YUV420;


    IMAGE3_S tmpImage;
    stParas.s32Sizemin = 40;
    tmpImage.s32W = videoWidth;
    tmpImage.s32H = videoHeight;
    tmpImage.pu8D1 = (IMP_U8*)malloc(sizeof(IMP_U8)*videoWidth*videoHeight*1.5);
    tmpImage.pu8D2 = tmpImage.pu8D1 + videoWidth*videoHeight;
    tmpImage.pu8D3 = tmpImage.pu8D2 + videoWidth*videoHeight/4;
    tmpImage.enFormat = IMAGE_FORMAT_IMP_YUV420;

    IMP_PicOutFrame *frame = NULL;
	uchar* tmpImageSrc = (IMP_U8*)malloc(sizeof(int)*videoWidth*videoHeight);
	
    stParas.s32Sizemax = 320;
	stParas.s32Sizemin = 48;
    stParas.s32Numax = 4;
    stParas.u32EnableColor = 0;
    stParas.u32Enablerotate = 0;
    stParas.u32RotateLevel = 0;
    stParas.s32Level = 2;
    stParas.s32Confidence = 0;
	stParas.QAlevel = 2;
    IMP_VFD_Config(handle,&stParas);
    FACEPATH face_path[IMP_VFD_MAX_FACE_NUMBER];
    memset(face_path, 0, sizeof(FACEPATH)*IMP_VFD_MAX_FACE_NUMBER);
    while(!stopped)
    {
        m_frame_queue->PeekFrame(&frame);
        if(NULL == frame)
        {
            usleep(100000);
            continue;
        }
		memcpy(tmpImageSrc,frame->pu8D1,sizeof(int)*videoWidth*videoHeight);
        //this->RGBA2YUV420P_QVideoFrame(tmpImageSrc,frame->nWidth,frame->nHeight,tmpImage.pu8D1);
        this->RGBA2YUV420P(tmpImageSrc,frame->nWidth,frame->nHeight,tmpImage.pu8D1);
        this->downSize(&tmpImage,&image);

        IMP_VFD_Process(handle,&image);
        IMP_VFD_GetResult(handle,&stResult);


        if(stResult.s32Facenumber == 0){
            memset(face_path, 0, sizeof(FACEPATH)*IMP_VFD_MAX_FACE_NUMBER);
        }

        if(stResult.s32Facenumber > 0)
        {
            for(int i = 0; i < 32; i ++)
            {
                int flag_isInScreen = 0;
                for(int j = 0; j < stResult.s32Facenumber; j ++)
                {
                    if(face_path[i].isUsed == 1 && face_path[i].ID == stResult.stFace[j].u32FaceID)
                    {
                        flag_isInScreen = 1;
                        break;
                    }
                }
                if(0 == flag_isInScreen)
                    face_path[i].isUsed = 0;
            }

            int tmpSizeTimes = 1;
            for(int i = 0; i < stResult.s32Facenumber; i ++)
            {

                int flag_isExist = 0;
                for(int j = 0; j < IMP_VFD_MAX_FACE_NUMBER; j ++)
                {
                    if(face_path[j].isUsed == 1 && face_path[j].ID == stResult.stFace[i].u32FaceID)
                    {
                        flag_isExist = 1;
                        break;
                    }
                }
                if(0 == flag_isExist)
                {

                    if(stResult.stFace[i].faceQA_Res == 1)
                    {
                        int startX = stResult.stFace[i].stPosition.s16X1 * tmpSizeTimes;
                        int endX = stResult.stFace[i].stPosition.s16X2 * tmpSizeTimes;
                        int startY = stResult.stFace[i].stPosition.s16Y1 * tmpSizeTimes;
                        int endY = stResult.stFace[i].stPosition.s16Y2 * tmpSizeTimes;
                        int faceW = (stResult.stFace[i].stPosition.s16X2 - stResult.stFace[i].stPosition.s16X1) * tmpSizeTimes;
                        int faceH = (stResult.stFace[i].stPosition.s16Y2 - stResult.stFace[i].stPosition.s16Y1) * tmpSizeTimes;
                        uchar *tmpM = (uchar*)malloc(sizeof(int)*faceW*faceH);
                        uchar *tmpN = tmpM;

                        for(int j = startY; j < endY; j ++)
                        {
                            memcpy(tmpM,frame->pu8D1 + j * frame->nWidth * sizeof(int) + startX * sizeof(int),faceW * sizeof(int));
                            tmpM += faceW * sizeof(int);
                        }
                        tmpM = tmpN;

                        /*tmpN = tmpM + (sizeof(int)*(faceW*faceH - 1));
                        for(int j = frame->nHeight - endY; j < (frame->nHeight - startY); j++)
                        {
                            for (int m = frame->nWidth - endX; m <(frame->nWidth - startX);m++)
                            {
                                memcpy(tmpN,tmpImageSrc + j * frame->nWidth * sizeof(int) + m * sizeof(int),sizeof(int));
                                tmpN -= sizeof(int);
                            }
                        }*/

                        QString t_imageName = this->_getPicName(stResult,i);
                        QString t_imageUrl = this->_saveFacePic(t_imageName,tmpM,faceW,faceH);



                        QString t_metaImageName = this->_getBigPicName(tmpSizeTimes,stResult,i,frame->nWidth);
                        QString t_metaImageUrl = this->_saveBigPic(t_metaImageName,tmpImageSrc, videoWidth,videoHeight);

                        QJsonObject json;
                        json.insert("name",t_imageName);
                        json.insert("imageUrl",t_imageUrl);
                        json.insert("metaImageName",t_metaImageName);
                        json.insert("metaImageUrl",t_metaImageUrl);

                        qDebug() << "face++ " << QString::number(RESULT_COUNT++);

                        this->setEmitVfdData(json);
                        for(int j = 0; j < IMP_VFD_MAX_FACE_NUMBER; j ++)
                        {
                            if(face_path[j].isUsed == 0)
                            {
                                face_path[j].isUsed = 1;
                                face_path[j].ID = stResult.stFace[i].u32FaceID;
                                face_path[j].isQA = stResult.stFace[i].faceQA_Res;
                                //face_path[i].path = tmpPath;
                                break;
                            }
                        }
                        free(tmpM);
                    }

                }
            }
        }
        m_frame_queue->RemoveFrame();
        usleep(100000);
    }
    IMP_VFD_Release(&handle);
    free(image.pu8D1);
    free(tmpImage.pu8D1);
    stopped = false;

    handle = Q_NULLPTR;
    delete handle;

    frame = Q_NULLPTR;
    delete frame;

    qDebug() << "exit vfd workder";
}

void VFDProcessor::stop()
{
    stopped = true;
}

void VFDProcessor::stopProcessor()
{
    this->stopped = true;
    if(m_frame_queue){
        m_frame_queue->ClearQueue();
    }

}

void VFDProcessor::resetProcessor()
{

    stopProcessor();
    this->is_processor_init = false;
}

void VFDProcessor::startProcessor()
{
    if(!is_processor_init) return;
    this->stopped = false;
    this->start();
}

void VFDProcessor::setEmitVfdData(QJsonObject &dataStr)
{
    emit sig_alg_result(QString(QJsonDocument(dataStr).toJson()));
}

void VFDProcessor::downSize(IMAGE3_S *pstSrc, IMAGE3_S *pstDst)
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

void VFDProcessor::RGBA2YUV420P(unsigned char *RgbaBuf,int nWidth,int nHeight,unsigned char *yuvBuf)
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

void VFDProcessor::RGBA2YUV420P_QVideoFrame(unsigned char *RgbaBuf, int nWidth, int nHeight, unsigned char *yuvBuf)
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

QString VFDProcessor::_getPicName(IMP_VFD_RESULT_S &stResult,int i) const
{
    //保存面部图片
    QString tmpID = QString::number(stResult.stFace[i].u32FaceID,10);
    QString picName("face_");
    picName.append(tmpID);
    if(stResult.stFace[i].faceQA_Res == 1)
    {
        picName.append("_QA");
    }
    else{
        picName.append("_common");
    }

    return picName;
}
QString VFDProcessor::_getBigPicName(int tmpSizeTimes, IMP_VFD_RESULT_S &stResult,int i,int nFrameWidth) const
{
    QString bigPicName("face_");
    QString tmpIDSrc = QString::number(stResult.stFace[i].u32FaceID,10);
    bigPicName.append(tmpIDSrc);
    if(stResult.stFace[i].faceQA_Res == 1)
        bigPicName.append("_QA");
    else
        bigPicName.append("_common");

    QString tmpPositonX1 = QString::number(nFrameWidth - stResult.stFace[i].stPosition.s16X2 * tmpSizeTimes,10);
    bigPicName.append("_").append(tmpPositonX1);
    QString tmpPositonY1 = QString::number(stResult.stFace[i].stPosition.s16Y1 * tmpSizeTimes,10);
    bigPicName.append("_").append(tmpPositonY1);
    QString tmpPositonX2 = QString::number(nFrameWidth - stResult.stFace[i].stPosition.s16X1 * tmpSizeTimes,10);
    bigPicName.append("_").append(tmpPositonX2);
    QString tmpPositonY2 = QString::number(stResult.stFace[i].stPosition.s16Y2 * tmpSizeTimes,10);
    bigPicName.append("_").append(tmpPositonY2);


    return bigPicName;
}
QString VFDProcessor::_saveFacePic(const QString imageName,uchar *tmpM, int faceW, int faceH) const
{
    QString abs_path = qApp->applicationDirPath();
    abs_path = abs_path.append("/").append(imageName).append(".jpg");
    QImage t_face_image(tmpM,faceW,faceH,QImage::Format_RGB32);
    t_face_image.save(abs_path,"JPG");
    return abs_path;
}
QString VFDProcessor::_saveBigPic(const QString imageName,uchar *imageSrc,int imageW,int imageH) const
{
    uchar* tmpframe = (IMP_U8*)malloc(sizeof(int)*imageW*imageH);
    uchar* tmpframeS = tmpframe;

    //save source image
    for(int i = imageH - 1; i >= 0; i --)
    {
        memcpy(tmpframe, imageSrc + i * imageW * sizeof(int),imageW * sizeof(int));
        tmpframe += imageW * sizeof(int);
    }
    tmpframe = tmpframeS;
    QString rootSrc = qApp->applicationDirPath();
    rootSrc.append("/").append(imageName).append(".jpg");
    QImage tmpSrc(tmpframe,imageW,imageH,QImage::Format_RGB32);
    tmpSrc.save(rootSrc,"JPG");

    tmpframeS = Q_NULLPTR;
    tmpframe = Q_NULLPTR;
    delete tmpframeS;
    delete tmpframe;

    return rootSrc;
}



