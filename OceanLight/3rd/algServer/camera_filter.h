#ifndef CAMERA_FILTER_H
#define CAMERA_FILTER_H

#include <QObject>
#include <QVideoFilterRunnable>

class CameraFilter : public QAbstractVideoFilter
{
    Q_OBJECT
public:
    explicit CameraFilter();
    ~CameraFilter();
signals:
    void sig_finished(QObject *result);
    void sig_cameraFrameSignal(QVideoFrame);
public slots:

    // QAbstractVideoFilter interface
public:
    QVideoFilterRunnable *createFilterRunnable();
};




class CameraFilterRunnable: public QVideoFilterRunnable
{
public:
    CameraFilterRunnable(CameraFilter* filter = Q_NULLPTR);
    ~CameraFilterRunnable();
private:
    CameraFilter *m_filter;

    // QVideoFilterRunnable interface
public:
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);
};

#endif // CAMERA_FILTER_H
