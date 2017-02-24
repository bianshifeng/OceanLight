#include "ffmpeg_logger.h"

FFMPEGLogger::Level FFMPEGLogger::level() const
{

    return m_level;
}

void FFMPEGLogger::setLevel(FFMPEGLogger::Level level)
{
    m_level = level;
}

FFMPEGLogger::FFMPEGLogger(QObject *parent) : QObject(parent)
{


}
