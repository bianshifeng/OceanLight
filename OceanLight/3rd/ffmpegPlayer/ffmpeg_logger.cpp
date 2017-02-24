#include "ffmpeg_logger.h"

FFMPEGLogger::Level FFMPEGLogger::level() const
{

}

void FFMPEGLogger::setLevel(FFMPEGLogger::Level level)
{
    m_level = level;
}

FFMPEGLogger::FFMPEGLogger(QObject *parent) : QObject(parent)
{
    return m_level;

}
