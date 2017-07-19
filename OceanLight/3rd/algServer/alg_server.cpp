#include "alg_server.h"

#include <QDebug>
#include <QImage>
#include <QVideoFrame>
#include <QApplication>


#include "ipd_processor/ipd_processor.h"
#include "vfd_processor/vfd_processor.h"
#include "pfr_processor/pfr_processor.h"


static int c_alg_image_index = 0;

AlgServer::AlgServer(QObject *parent) : QObject(parent),
    m_ptr_ipd_processor(Q_NULLPTR),
    m_ptr_vfd_processor(Q_NULLPTR),
    m_ptr_pfr_processor(Q_NULLPTR),
    m_isIpdActive(false),
    m_isVfdActive(false),
    m_isPfrActive(false)
{
    this->add_ipd_processor();
    this->add_vfd_processor();
    this->add_pfr_processor();
}

bool AlgServer::isIpdActive() const
{
    return m_isIpdActive;
}

bool AlgServer::isVfdActive() const
{
    return m_isVfdActive;
}

bool AlgServer::isPfrActive() const
{
    return m_isPfrActive;
}


void AlgServer::setImageFrame(const QImage &image)
{
    //QVideoFrame m_frame(image);
    if(m_ptr_ipd_processor){this->push_ipd_videoImage(image);}
    if(m_ptr_vfd_processor){this->push_vfd_videoImage(image);}

}
void AlgServer::setVideoFrame(const QVideoFrame &frame)
{
    QVideoFrame new_frame(m_ptr_ipd_processor->imageFromVideoFrame_convert(frame));
    if(m_ptr_ipd_processor){this->push_ipd_videoFrame(new_frame);}
    if(m_ptr_vfd_processor){this->push_vfd_videoFrame(new_frame);}
}


void AlgServer::serverReset()
{

    if(m_ptr_ipd_processor){
        this->setIsIpdActive(false);
        this->m_ptr_ipd_processor->resetProcessor();
    }


    if(m_ptr_vfd_processor){
        this->setIsVfdActive(false);
        this->m_ptr_vfd_processor->resetProcessor();
    }

    if(m_ptr_pfr_processor){
        this->setIsPfrActive(false);
        this->m_ptr_pfr_processor->resetProcessor();
    }
}

void AlgServer::resetVFD()
{
    if(m_ptr_vfd_processor){
        this->setIsVfdActive(false);
        this->m_ptr_vfd_processor->resetProcessor();
    }

}

void AlgServer::add_ipd_processor()
{
    if(m_ptr_ipd_processor == Q_NULLPTR){
        m_ptr_ipd_processor = new IPDProcessor();
        connect(m_ptr_ipd_processor,SIGNAL(sig_alg_result(QString)),this,SIGNAL(sig_alg_ipd_data(QString)));
    }
}
void AlgServer::setIsIpdActive(bool isIpdActive)
{
    if (m_isIpdActive == isIpdActive)
        return;
    m_isIpdActive = isIpdActive;
    emit isIpdActiveChanged(isIpdActive);
}
void AlgServer::push_ipd_videoFrame(const QVideoFrame &frame)
{

    if(!m_isIpdActive) return;

    if(!m_ptr_ipd_processor->is_processor_init){
        m_ptr_ipd_processor->initFrameQueue(frame.width(),frame.height());
        qDebug() << "m_ptr_ipd_processor->initFrameQueue";
        qDebug() << frame.width();
        m_ptr_ipd_processor->startProcessor();
    }
    m_ptr_ipd_processor->push_video_frame(frame);



}

void AlgServer::push_ipd_videoImage(const QImage &image)
{
    if(!m_isIpdActive) return;

    if(!m_ptr_ipd_processor->is_processor_init){
        m_ptr_ipd_processor->initFrameQueue(image.width(),image.height());
        qDebug() << "m_ptr_ipd_processor->initFrameQueue";
        qDebug() << image.width();
        m_ptr_ipd_processor->startProcessor();
    }
    m_ptr_ipd_processor->push_video_image(image);

}

void AlgServer::add_vfd_processor()
{
    if(m_ptr_vfd_processor == Q_NULLPTR){
        m_ptr_vfd_processor = new VFDProcessor();
        connect(m_ptr_vfd_processor,SIGNAL(sig_alg_result(QString)),this,SIGNAL(sig_alg_vfd_data(QString)));
    }

}
void AlgServer::setIsVfdActive(bool isVfdActive)
{
    if (m_isVfdActive == isVfdActive)
        return;
    m_isVfdActive = isVfdActive;
    emit isVfdActiveChanged(isVfdActive);
}
void AlgServer::push_vfd_videoFrame(const QVideoFrame &frame)
{
    if(!m_isVfdActive) return;

    if(!m_ptr_vfd_processor->is_processor_init){
        m_ptr_vfd_processor->initFrameQueue(frame.width(),frame.height());
        qDebug() << "m_ptr_vfd_processor->initFrameQueue";
        qDebug() << frame.width();
        m_ptr_vfd_processor->startProcessor();
    }

    m_ptr_vfd_processor->push_video_frame(frame);

}

void AlgServer::push_vfd_videoImage(const QImage &image)
{
    if(!m_isVfdActive) return;

    if(!m_ptr_vfd_processor->is_processor_init){
        m_ptr_vfd_processor->initFrameQueue(image.width(),image.height());
        m_ptr_vfd_processor->startProcessor();
    }

    m_ptr_vfd_processor->push_video_image(image);

}

void AlgServer::add_pfr_processor()
{
    if(m_ptr_pfr_processor == Q_NULLPTR){
        m_ptr_pfr_processor = new PFRProcessor();
        connect(m_ptr_pfr_processor,SIGNAL(sig_alg_result(QString)),this,SIGNAL(sig_alg_pfr_data(QString)));
        connect(m_ptr_pfr_processor,SIGNAL(sig_reg_result(QString)),this,SIGNAL(sig_alg_pfr_reg_data(QString)));
    }

}
void AlgServer::setIsPfrActive(bool isPfrActive)
{
    if (m_isPfrActive == isPfrActive)
        return;

    m_isPfrActive = isPfrActive;
    emit isPfrActiveChanged(isPfrActive);
}
void AlgServer::push_pfr_imageFrame(const QString &imageName, const QString &imageUrl, int regOrRec)
{

    if(!m_isPfrActive) return;

    if(!m_ptr_pfr_processor->is_processor_init){
        m_ptr_pfr_processor->initFrameQueue();
        m_ptr_pfr_processor->startProcessor();
    }

    QString t_imageName = imageName;
    QString t_imageUrl = imageUrl;
    t_imageUrl.replace("file:///","");
    //QString xx = qApp->applicationDirPath();
    //xx.append("/face_7_QA_395_230_537_372.jpg");
    m_ptr_pfr_processor->push_frame(t_imageUrl,regOrRec,t_imageName);

}


