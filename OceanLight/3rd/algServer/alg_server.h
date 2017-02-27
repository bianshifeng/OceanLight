#ifndef ALG_SERVER_H
#define ALG_SERVER_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QImage>
#include <QUrl>


class QVideoFrame;
class AlgServer : public QObject
{
    Q_OBJECT

    Q_DISABLE_COPY(AlgServer)
public:
    static AlgServer* _instance;
    static QObject* qml_singleton_provider(QQmlEngine *qmlEngine,QJSEngine *jsEngine)
    {
        Q_UNUSED(qmlEngine);
        Q_UNUSED(jsEngine);
        return _instance = new AlgServer();
    }

    Q_INVOKABLE void setCameraImage(const QString& imageUrl);


signals:

    void sig_alg_test_data(const QString& message);

public slots:

    void setImage(const QImage& image);

    void setVideoFrame(const QVideoFrame& frame);

    QImage imageFromVideoFrame(const QVideoFrame& buffer) const;

private:
    explicit AlgServer(QObject *parent = 0);
};

#endif // ALG_SERVER_H
