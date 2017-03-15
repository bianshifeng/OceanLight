#include "alg_server.h"

#include <QDebug>
#include <QImage>
#include <QVideoFrame>


#include "ipd_processor/ipd_processor.h"
#include "vfd_processor/vfd_processor.h"
#include "pfr_processor/pfr_processor.h"

static int c_alg_image_index = 0;

AlgServer::AlgServer(QObject *parent) : QObject(parent),
    m_ptr_ipd_processor(Q_NULLPTR),
    m_ptr_vfd_processor(Q_NULLPTR),
    m_ptr_pfr_processor(Q_NULLPTR),
    m_is_vfd_processor_init(false),
    m_is_pfr_processor_init(false),
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

void AlgServer::setVideoFrame(const QVideoFrame &frame)
{
    if(m_ptr_ipd_processor){this->push_ipd_videoFrame(frame);}
    if(m_ptr_vfd_processor){this->push_vfd_videoFrame(frame);}
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

    if(!m_ptr_ipd_processor->is_processor_init){
        m_ptr_ipd_processor->initFrameQueue(frame.width(),frame.height());
        m_ptr_ipd_processor->startProcessor();
    }
    if(m_isIpdActive){
            m_ptr_ipd_processor->push_video_frame(frame);
    }


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
    if(!m_is_vfd_processor_init){
        m_ptr_vfd_processor->set_video_resolution(frame.width(),frame.height());
        m_ptr_vfd_processor->initFrameQueue();
        m_ptr_vfd_processor->startProcessor();
        m_is_vfd_processor_init = true;

    }

    if(m_isVfdActive){
        m_ptr_vfd_processor->push_video_frame(frame);
    }
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

    if(!m_is_pfr_processor_init){
        m_ptr_pfr_processor->initFrameQueue();
        m_ptr_pfr_processor->startProcessor();
        m_is_pfr_processor_init = true;
    }

    if(m_isPfrActive){
        QString t_imageName = imageName;
        QString t_imageUrl = imageUrl;
        t_imageUrl.replace("file:///","");
        m_ptr_pfr_processor->push_frame(t_imageUrl,regOrRec,t_imageName);
    }
}


