#ifndef FFMPEG_LOGGER_H
#define FFMPEG_LOGGER_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>

#define AV_LOG_PANIC 1
#define AV_LOG_FATAL 1
#define AV_LOG_ERROR 1
#define AV_LOG_WARNING 1
#define AV_LOG_INFO 1
#define AV_LOG_VERBOSE 1
#define AV_LOG_DEBUG 1


class FFMPEGLogger : public QObject
{
    Q_OBJECT

    Q_ENUMS(Level)

    Q_PROPERTY(Level level READ level WRITE setLevel)
    Q_PROPERTY(bool defaultBehavior MEMBER _defaultBehaviour)

public:
    enum Level{
        Panic = AV_LOG_PANIC,
        Fatal = AV_LOG_FATAL,
        Warning = AV_LOG_WARNING,
        Error = AV_LOG_ERROR,
        Info = AV_LOG_INFO,
        Verbose = AV_LOG_VERBOSE,
        Debug = AV_LOG_DEBUG,

    };

    static FFMPEGLogger* _instance;
    static QObject* GetInstance(QQmlEngine*,QJSEngine*)
    {
        return _instance = new FFMPEGLogger();

    }
    Level level() const;

signals:
    void log(
            Level level,
            const QString& message,
            const QString& classname,
            const QString& url);

public slots:
    void setLevel(Level level);

private:
    explicit FFMPEGLogger(QObject *parent = 0);
    Level m_level;
    bool _defaultBehaviour = true;

};

Q_DECLARE_METATYPE(FFMPEGLogger::Level)  //通过Q_DECLARE_METATYPE声明后，就可以让自定义的类型设置到QVariant
#endif // FFMPEG_LOGGER_H
