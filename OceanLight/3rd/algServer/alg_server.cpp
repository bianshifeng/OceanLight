#include "alg_server.h"

#include <QDebug>
#include <QImage>
#include <QVideoFrame>


#include "ipd_processor/ipd_processor.h"
#include "vfd_processor/vfd_processor.h"

static int c_alg_image_index = 0;

AlgServer::AlgServer(QObject *parent) : QObject(parent),
    m_ptr_ipd_processor(Q_NULLPTR),
    m_ptr_vfd_processor(Q_NULLPTR),
    m_is_processor_init(false)
{

    m_ptr_ipd_processor = new IPDProcessor();
    m_ptr_vfd_processor = new VFDProcessor();
    connect(m_ptr_ipd_processor,SIGNAL(sig_alg_result(QString)),this,SIGNAL(sig_alg_warning_data(QString)));
    connect(m_ptr_vfd_processor,SIGNAL(sig_alg_result(QString)),this,SIGNAL(sig_alg_warning_data(QString)));
}


bool AlgServer::initProcessor(const int &img_width, const int &img_height)
{
    m_ptr_ipd_processor->set_video_resolution(img_width,img_height);
    m_ptr_ipd_processor->initFrameQueue();
    m_ptr_ipd_processor->start();

    m_ptr_vfd_processor->set_video_resolution(img_width,img_height);
    m_ptr_vfd_processor->initFrameQueue();
    m_ptr_vfd_processor->start();

    m_is_processor_init = true;
    return true;
}


void AlgServer::setVideoFrame(const QVideoFrame &frame)
{
    if(!m_is_processor_init){
        this->initProcessor(frame.width(),frame.height());
    }else{
        m_ptr_ipd_processor->push_video_frame(frame);
        m_ptr_vfd_processor->push_video_frame(frame);
        c_alg_image_index++;
        emit sig_alg_test_data(QString::number(c_alg_image_index));
    }
}




QImage AlgServer::imageFromVideoFrame(const QVideoFrame &buffer) const
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

