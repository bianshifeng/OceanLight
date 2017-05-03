#ifndef FFMPEG_WORKER_H
#define FFMPEG_WORKER_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>

class FFmpegWorker : public QObject
{
    Q_OBJECT
public:
    explicit FFmpegWorker(QObject *parent = 0);

    void* createImage(int width, int height, int &align);

signals:

public slots:
    void receiving();

private:
    QTimer m_playTimer;
    QElapsedTimer m_elapsedTimer;

    QByteArray m_data_image;
    QByteArray m_data_sound;


};

#endif // FFMPEG_WORKER_H
