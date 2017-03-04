#ifndef ALG_SERVER_H
#define ALG_SERVER_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QImage>
#include <QUrl>

class IPDProcessor;
class VFDProcessor;
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
signals:
    void sig_alg_test_data(const QString& message);
    void sig_alg_warning_data(const QString& message);

public slots:
    void setVideoFrame(const QVideoFrame& frame);
    bool initProcessor(const int &img_width, const int &img_height );
    QImage imageFromVideoFrame(const QVideoFrame& buffer) const;

private:
    explicit AlgServer(QObject *parent = 0);

    IPDProcessor* m_ptr_ipd_processor;
    VFDProcessor* m_ptr_vfd_processor;
    bool m_is_processor_init;
};

#endif // ALG_SERVER_H
