#include "camera_filter.h"

#include"alg_server.h"


static int c_frame_index_count = 0;
CameraFilter::CameraFilter()
{

}

CameraFilter::~CameraFilter()
{

}

QVideoFilterRunnable *CameraFilter::createFilterRunnable()
{
    return new CameraFilterRunnable(this);
}

CameraFilterRunnable::CameraFilterRunnable(CameraFilter *filter)
{
    m_filter = filter;
}

CameraFilterRunnable::~CameraFilterRunnable()
{

}

QVideoFrame CameraFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, QVideoFilterRunnable::RunFlags flags)
{
    QVideoFrame cloneFrame(*input);
    if(c_frame_index_count >=10){
        AlgServer::_instance->setVideoFrame(cloneFrame);
        c_frame_index_count = 0;
    }
    c_frame_index_count++;
    return cloneFrame;
}
