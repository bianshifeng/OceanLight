/*
** ffmpeg media stream player binding for qtmultimedia
** https://github.com/undwad/qmlffmpeg mailto:undwad@mail.ru
** see copyright notice in ./LICENCE
*/

#pragma once

#include <QObject>
#include <QString>
#include <QQuickItem>
#include <QList>
#include <QThread>
#include <QElapsedTimer>
#include <QTimer>
#include <QByteArray>
#include <QJSValue>
#include <QJSValueIterator>
#include <QDebug>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QVideoFrame>
#include <QAudioFormat>
#include <QAudioOutput>

#include <climits>
#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <ctime>
#include <chrono>
#include <queue>
#include <map>

using namespace std;
using namespace std::chrono;

//#define AV_LOG_LEVEL AV_LOG_VERBOSE

using namespace std;

#include "Channel.h"

typedef map<string, string> FFMPEGParams;

Q_DECLARE_METATYPE(FFMPEGParams)

class FFMPEGWorker : public QObject, ffmpeg::Channel
{
    Q_OBJECT

public:
    FFMPEGWorker() : ffmpeg::Channel(AVPixelFormat::AV_PIX_FMT_RGBA, AV_SAMPLE_FMT_S16), _timer(this)
    {
        _timer.setInterval(1);
        _timer.setSingleShot(false);
        connect(&_timer, &QTimer::timeout, this, &FFMPEGWorker::receiving);
    }

    virtual bool interrupt() { return false; }

    virtual void* createImage(int width, int height, int& align)
    {
        QVideoSurfaceFormat format(QSize(width, height), QVideoFrame::Format_BGR32);
        format.setFrameRate((qreal)(videoCodec->time_base.den / videoCodec->time_base.num));
        emit startVideoSurface(format);
        _image.resize(width * height * av_get_bits_per_pixel(av_pix_fmt_desc_get(pixelFormat)) / 8);
        return _image.data();
    }
    virtual void lockImage() { }
    virtual void unlockImage() { }

    virtual void* createSound(AVSampleFormat sampleFormat, int channelCount, int sampleCount, int bitRate, int sampleRate, int& align)
    {
        _audioInterval = 1000 * sampleCount / sampleRate;
        _sound.resize(av_samples_get_buffer_size(nullptr, channelCount, sampleCount, sampleFormat, align));
        QAudioFormat format;
        format.setChannelCount(channelCount);
        format.setCodec("audio/pcm");
        format.setSampleRate(sampleRate);
        format.setSampleSize(bitRate);
        switch(sampleFormat)
        {
        case AV_SAMPLE_FMT_U8:
        case AV_SAMPLE_FMT_U8P: format.setSampleType(QAudioFormat::UnSignedInt); break;
        case AV_SAMPLE_FMT_S16:
        case AV_SAMPLE_FMT_S32:
        case AV_SAMPLE_FMT_S16P:
        case AV_SAMPLE_FMT_S32P: format.setSampleType(QAudioFormat::SignedInt); break;
        case AV_SAMPLE_FMT_FLT:
        case AV_SAMPLE_FMT_DBL:
        case AV_SAMPLE_FMT_FLTP:
        case AV_SAMPLE_FMT_DBLP: format.setSampleType(QAudioFormat::Float); break;
        default: format.setSampleType(QAudioFormat::Unknown);
        }
        _audioOutput = new QAudioOutput(format);
        _audioInput = _audioOutput->start();
        return _sound.data();
    }

    virtual void lockSound() { }
    virtual void unlockSound() { }

    virtual void free()
    {
        ffmpeg::Channel::free();
        if(_audioOutput) delete _audioOutput;
    }

public slots:
    void toPlay(const QString& source, const FFMPEGParams& params)
    {
        reset(source.toStdString().c_str(), params);
        _videoTimeStamp = _audioTimeStamp = 0;
        _timer.start();
    }

    void toSetVolume(qreal volume) { if(_audioOutput) _audioOutput->setVolume(volume); }

    void receiving()
    {
        receive();

        if(0 == _audioInterval && hasVideo()) _audioInterval = 1000 * videoCodec->time_base.num / videoCodec->time_base.den;

        if(0 == _audioTimeStamp) _elapsed.restart();

        if(_elapsed.elapsed() >= _audioTimeStamp)
            if(hasAudio())
            {
                qint64 timestamp = popAudioSample();
                if (timestamp >= 0)
                {
                    _audioTimeStamp = timestamp;
                    _audioInput->write(_sound.data(), _sound.size());
                }
            }
            else _audioTimeStamp += _audioInterval;

        if(hasVideo())
            while(_videoTimeStamp < _audioTimeStamp)
            {
                int timestamp = popVideoFrame();
                if(timestamp >= 0)
                {
                    _videoTimeStamp = timestamp;
                    QVideoFrame frame(_image.size(), QSize(videoCodec->width, videoCodec->height), _image.size() / videoCodec->height, QVideoFrame::Format_BGR32);
                    if(frame.map(QAbstractVideoBuffer::WriteOnly))
                    {
                        memcpy(frame.bits(), _image.data(), _image.size());
                        frame.unmap();
                        emit presentVideoSurface(frame);
                    }
                }
                else break;
            }

        qreal volume = hasAudio() ? _audioOutput->volume() : -1;
        if(volume != _volume)
        {
            _volume = volume;
            emit volumeChanged(volume);
        }
    }

    void toStop()
    {
        _timer.stop();
        emit stopVideoSurface();
    }

signals:
    void startVideoSurface(const QVideoSurfaceFormat& format);
    void presentVideoSurface(const QVideoFrame& frame);
    void stopVideoSurface();
    void volumeChanged(qreal);

private:
    QByteArray _image;
    QByteArray _sound;
    QAudioOutput* _audioOutput = nullptr;
    QIODevice* _audioInput = nullptr;
    QTimer _timer;
    QElapsedTimer _elapsed;
    qint64 _audioTimeStamp = 0;
    qint64 _videoTimeStamp = 0;
    qint64 _audioInterval = 0;
    qreal _volume = 0;
};

class FFMPEGPlayer : public QObject
{
public:
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QAbstractVideoSurface* videoSurface MEMBER _videoSurface)
    Q_PROPERTY(bool playing READ playing WRITE setPlaying NOTIFY playingChanged)
    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(QJSValue params READ params WRITE setParams NOTIFY paramsChanged)

    Q_DISABLE_COPY(FFMPEGPlayer)

signals:
    void toPlay(const QString& source, const FFMPEGParams& params);
    void toStop();
    void toSetVolume(qreal volume);
    void playingChanged(bool);
    void volumeChanged(qreal);
    void paramsChanged(const QJSValue&);
    void sourceChanged(const QString&);
    void error(const QString& error);

public:
    FFMPEGPlayer(QQuickItem *parent = 0) : QObject(parent)
    {
        _worker->moveToThread(&_thread);
        connect(&_thread, &QThread::finished, _worker, &QObject::deleteLater);
        connect(this, &FFMPEGPlayer::toPlay, _worker, &FFMPEGWorker::toPlay);
        connect(this, &FFMPEGPlayer::toStop, _worker, &FFMPEGWorker::toStop);
        connect(this, &FFMPEGPlayer::toSetVolume, _worker, &FFMPEGWorker::toSetVolume);
        connect(_worker, &FFMPEGWorker::volumeChanged, this, [this](qreal volume)
        {
            if(_volume != volume)
            {
                _volume = volume;
                emit volumeChanged(volume);
            }
        });
        connect(_worker, &FFMPEGWorker::startVideoSurface, this, [this](const QVideoSurfaceFormat& format)
        {
            setPlaying(false);
            if(!_videoSurface->start(format))
                emitVideoSurfaceError();
        });
        connect(_worker, &FFMPEGWorker::presentVideoSurface, this, [this](const QVideoFrame& frame)
        {
            _frame = frame;
            if(_videoSurface->present(frame)) setPlaying(true);
            else emitVideoSurfaceError();
        });
        connect(_worker, &FFMPEGWorker::stopVideoSurface, this, [this]()
        {
            setPlaying(false);
            _videoSurface->stop();
        });
        _thread.start();
    }

    bool playing() const { return _playing; }
    void setPlaying(bool playing)
    {
        if(playing != _playing)
        {
            _playing = playing;
            emit playingChanged(playing);
        }
    }

    qreal volume() const { return _volume; }
    void setVolume(qreal volume) { emit toSetVolume(volume); }

    QJSValue params() const { return _params; }

    void setParams(const QJSValue& params)
    {
        _params = params;
        __params.clear();
        QJSValueIterator it(params);
        while (it.hasNext()) 
        {
            it.next();
            __params.insert(pair<string, string>(it.name().toStdString(), it.value().toString().toStdString()));
        }
        emit paramsChanged(params);
    }

    QString source() const { return _source; }
    void setSource(const QString& source)
    {
        if(source != _source)
        {
            _source = source;
            emit sourceChanged(source);
        }
    }

    ~FFMPEGPlayer()
    {
        stop();
        _thread.quit();
        _thread.wait();
    }

public slots:
    void play() { emit toPlay(_source, __params); }

    void stop() { emit toStop(); }

    bool save(const QString& path, int width = 0)
    {
        if(_frame.map(QAbstractVideoBuffer::ReadOnly))
        {
            QImage image
            (
                _frame.bits(),
                _frame.width(),
                _frame.height(),
                _frame.bytesPerLine(),
                QImage::Format_RGBA8888
            );
            const_cast<QVideoFrame&>(_frame).unmap();
            return image.scaledToWidth(width ? width : _frame.width(), Qt::SmoothTransformation).save(path);
        }
        return false;
    }

private slots:

private:
    QString _source;
    QAbstractVideoSurface* _videoSurface;
    FFMPEGWorker* _worker = new FFMPEGWorker;
    QThread _thread;
    bool _playing = false;
    qreal _volume = 0;
    QJSValue _params;
    FFMPEGParams __params;
    QVideoFrame _frame;

    void emitVideoSurfaceError()
    {
        switch (_videoSurface->error())
        {
        case QAbstractVideoSurface::UnsupportedFormatError: emit error("video format was not supported"); break;
        case QAbstractVideoSurface::IncorrectFormatError: emit error("video frame was not compatible with the format of the surface"); break;
        case QAbstractVideoSurface::StoppedError: emit error("surface has not been started"); break;
        case QAbstractVideoSurface::ResourceError: emit error("surface could not allocate some resource"); break;
        }
    }
};

class FFMPEGLogger : public QObject
{
    Q_OBJECT

    Q_ENUMS(Level)

    Q_PROPERTY (Level level READ level WRITE setLevel)
    Q_PROPERTY (bool defaultBehaviour MEMBER _defaultBehaviour)

    Q_DISABLE_COPY(FFMPEGLogger)

public:
    static FFMPEGLogger* _instance;

    enum Level
    {
        Panic = AV_LOG_PANIC,
        Fatal = AV_LOG_FATAL,
        Error = AV_LOG_ERROR,
        Warning = AV_LOG_WARNING,
        Info = AV_LOG_INFO,
        Verbose = AV_LOG_VERBOSE,
        Debug = AV_LOG_DEBUG,
    };

    static QObject* provider(QQmlEngine*, QJSEngine*)
    {
        av_log_set_callback(log_callback);
        return _instance = new FFMPEGLogger();
    }

    FFMPEGLogger() { }

    Level level() const { return (Level)av_log_get_level(); }
    void setLevel(Level level) { av_log_set_level(level); }

    static void log_callback(void* avcl, int level, const char* format, va_list args)
    {
        if(level <= av_log_get_level())
        {
            if(_instance->_defaultBehaviour) av_log_default_callback(avcl, level, format, args);
            static int size = 256;
            string msg;
            msg.resize(size);
            int s = vsnprintf((char*)msg.c_str(), size, format, args);
            if(s >= 0)
            {
                if(s > size)
                {
                    size = s;
                    msg.resize(size);
                    s = vsnprintf((char*)msg.c_str(), size, format, args);
                }
                if('\n' == msg[s - 1])
                    msg[s - 1] = 0;
            }

            string classname;
            string url;
            if(avcl)
            {
                AVClass* avc = *(AVClass**)avcl;
                classname = (const char*)avc->class_name;
                if(0 == strcmp(avc->class_name, "AVFormatContext"))
                    url = (const char*)((AVFormatContext*)avcl)->filename;
                else if (0 == strcmp(avc->class_name, "URLContext"))
                    url = (const char*)((URLContext*)avcl)->filename;
            }

            emit _instance->log((Level)level, QString(msg.c_str()), QString(classname.c_str()), QString(url.c_str()));
        }
    }

signals:
    void log(Level level, const QString& message, const QString& classname, const QString& url);

public slots:
    QString levelToString(Level level)
    {
        switch(level)
        {
        case Panic: return "PANIC";
        case Fatal: return "FATAL";
        case Error: return "ERROR";
        case Warning: return "WARNING";
        case Info: return "INFO";
        case Verbose: return "VERBOSE";
        case Debug: return "DEBUG";
        default: return "UNKNOWN";
        }
    }

private:
    bool _defaultBehaviour = true;
};

Q_DECLARE_METATYPE(FFMPEGLogger::Level)
