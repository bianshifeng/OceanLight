#include "alg_server.h"

#include <QDebug>
#include <QImage>
#include <QVideoFrame>

static int c_alg_image_index = 0;
void AlgServer::setCameraImage(const QString& imageUrl)
{
    Q_UNUSED(imageUrl);

}

void AlgServer::setImage(const QImage &image)
{
    Q_UNUSED(image);


}

void AlgServer::setVideoFrame(const QVideoFrame &frame)
{

    //qDebug("w(%d),h(%d) format(%d) used(%d) bits(%d) mapped(%d)\n",frame.width(),frame.height(),frame.pixelFormat(),frame.isValid(),frame.bits(),frame.mappedBytes());
    c_alg_image_index++;
    emit sig_alg_test_data(QString::number(c_alg_image_index));
    imageFromVideoFrame(frame);
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

AlgServer::AlgServer(QObject *parent) : QObject(parent)
{

}
