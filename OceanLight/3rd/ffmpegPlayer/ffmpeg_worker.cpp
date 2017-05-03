#include "ffmpeg_worker.h"

#include <QVideoSurfaceFormat>
#include <QVideoFrame>

FFmpegWorker::FFmpegWorker(QObject *parent) : QObject(parent),
    m_playTimer(this)
{
    m_playTimer.setInterval(1);
    m_playTimer.setSingleShot(false);
    connect(&m_playTimer,SIGNAL(timeout()),this,SLOT(receiving()));
}

void *FFmpegWorker::createImage(int width, int height, int &align)
{
    Q_UNUSED(&align)
    QVideoSurfaceFormat t_format(QSize(width,height),QVideoFrame::Format_BGR32);
    t_format.setFrameRate(111);
    int t_dataSize =121;
    m_data_image.resize(t_dataSize);
    return m_data_image.data();
}
