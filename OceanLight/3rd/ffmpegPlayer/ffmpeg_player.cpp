#include "ffmpeg_player.h"

#include <QJSValueIterator>

#include "ffmpeg_worker.h"

FFmpegPlayer::FFmpegPlayer(QObject *parent) : QObject(parent),
    m_worker(Q_NULLPTR)
{

    m_worker = new FFmpegWorker(this);

}

QString FFmpegPlayer::source() const
{
    return m_source;
}

QJSValue FFmpegPlayer::params() const
{
    return m_params;
}

qreal FFmpegPlayer::volume() const
{
    return m_volume;
}

void FFmpegPlayer::setsource(QString source)
{
    if (m_source == source)
        return;

    m_source = source;
    emit sourceChanged(source);
}

void FFmpegPlayer::setParams(QJSValue params)
{
    m_params = params;
    m_mediaParams.clear();
    QJSValueIterator t_it(params);
    while (t_it.hasNext())
    {
        t_it.next();
        m_mediaParams.insert(pair<string,string>(t_it.name().toStdString(),t_it.value().toString().toStdString()));
    }
    emit paramsChanged(params);
}

void FFmpegPlayer::setVolume(qreal volume)
{
    if (m_volume == volume)
        return;

    m_volume = volume;
    emit volumeChanged(volume);
}

void FFmpegPlayer::handleVideoSurfaceError()
{
    switch (m_videoSurface->error()) {
    case QAbstractVideoSurface::UnsupportedFormatError:
        emit this->error("Video format was not supported");
        break;
    case QAbstractVideoSurface::IncorrectFormatError:
        emit this->error("Video frame was not compatible with the format of the surface");
        break;
    case QAbstractVideoSurface::StoppedError:
        emit this->error("Surface has been stopped error");
        break;
    case QAbstractVideoSurface::ResourceError:
        emit this->error("Surface could not allocate meida resource");
        break;
    }
}

void FFmpegPlayer::startVideoSurfaceByFormat(const QVideoSurfaceFormat &format)
{
    if(!m_videoSurface->start(format))
    {
        this->handleVideoSurfaceError();
    }

}

void FFmpegPlayer::presentVideoSurfaceByFrame(const QVideoFrame &frame)
{
    QVideoFrame m_frame= frame;
    if(!m_videoSurface->present(m_frame)){
        this->handleVideoSurfaceError();
    }

}

void FFmpegPlayer::stopVideoSurface()
{
    m_videoSurface->stop();
}
