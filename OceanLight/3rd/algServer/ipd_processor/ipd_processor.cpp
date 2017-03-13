#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include "ipd_processor.h"
#include "imp_ipd_api.h"
using namespace std;

IPDProcessor::IPDProcessor():AlgProcessor()
{
    this->m_alg_type = AlgServer::Alg_IPD;
}

void IPDProcessor::run()
{
    IMP_S32 width = this->videoWidth;
    IMP_S32 height = this->videoHeight;
    IMP_HANDLE handle;

    qDebug() << QString::number(width) << "x" << QString::number(height);

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
    uchar* tmpframe = (IMP_U8*)malloc(sizeof(int)*videoWidth*videoHeight);
    uchar* tmpframeS = tmpframe;

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
        this->RGBA2YUV420P_QVideoFrame(frame->pu8D1,frame->nWidth,frame->nHeight,tmpImage.pu8D1);
        this->downSize(&tmpImage,&image);
        IMP_IPD_Process(handle,&image,NULL,&stResult);
        frame_count ++;
        if(stResult.s32TgtNum > 0)ipd_count++;
        if(frame_count%10 == 0)
        {
            if(ipd_count > 7 && isWarning == 0)
            {
                for(int i = frame->nHeight -1 ; i >=0;i--)
                {
                    memcpy(tmpframe,frame->pu8D1 + i * frame->nWidth * sizeof(int), frame->nWidth * sizeof(int));
                    tmpframe += frame->nWidth * sizeof(int);
                }
                tmpframe = tmpframeS;

                QString imageName;
                imageName = imageName.append("ipd_").append(QString::number(frame_count,10));
                QString imageSavePath = this->saveImageFrameMetaData(imageName,tmpframe,frame->nWidth,frame->nHeight,QImage::Format_RGB32);
                QJsonObject json;
                json.insert("name",imageName);
                json.insert("status",QString("warning"));
                json.insert("imageUrl",imageSavePath);
                this->setEmitIpdData(json);
                isWarning = 1;
            }
            if(ipd_count < 7 && isWarning == 1)
            {
                QJsonObject json;
                json.insert("name",QString("IPD"));
                json.insert("status",QString("clear"));
                json.insert("imageUrl","");
                this->setEmitIpdData(json);
                isWarning = 0;

            }
            ipd_count = 0;

        }
        m_frame_queue->RemoveFrame();
        usleep(100000);
    }



    IMP_IPD_Release(handle);
    free(image.pu8D1);
    free(tmpImage.pu8D1);
    stopped = false;
}



void IPDProcessor::setEmitIpdData(QJsonObject &dataStr)
{

    emit sig_alg_result(QString(QJsonDocument(dataStr).toJson()));
}
