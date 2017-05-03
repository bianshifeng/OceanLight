#ifndef FFMPEG_PLAYER_H
#define FFMPEG_PLAYER_H

#include <map>

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QJSValue>
#include <QObject>
#include <QThread>

using namespace std;

typedef map<string,string> MediaParams;
Q_DECLARE_METATYPE(MediaParams)

class FFmpegWorker;

class FFmpegPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setsource NOTIFY sourceChanged)
    Q_PROPERTY(QAbstractVideoSurface* videoSurface MEMBER m_videoSurface)
    Q_PROPERTY(QJSValue params READ params WRITE setParams NOTIFY paramsChanged)
    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)

    Q_DISABLE_COPY(FFmpegPlayer)
public:
    explicit FFmpegPlayer(QObject *parent = 0);
    QString source() const;
    QJSValue params() const;
    qreal volume() const;

public slots:
    void setsource(QString source);
    void setParams(QJSValue params);
    void setVolume(qreal volume);

signals:
    void error(const QString& error);
    void sourceChanged(QString source);
    void paramsChanged(QJSValue params);
    void volumeChanged(qreal volume);


private:
    void handleVideoSurfaceError();
    void startVideoSurfaceByFormat(const QVideoSurfaceFormat& format);
    void presentVideoSurfaceByFrame(const QVideoFrame& frame);
    void stopVideoSurface();

private:
    QString m_source;
    QJSValue m_params;
    qreal m_volume;
    QAbstractVideoSurface* m_videoSurface;


    //inner
    MediaParams m_mediaParams;
    QThread m_thread;
    FFmpegWorker m_worker;

};

#endif // FFMPEG_PLAYER_H
