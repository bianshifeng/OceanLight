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

    Q_ENUMS(AlgType)
    Q_DISABLE_COPY(AlgServer)

    Q_PROPERTY(bool isIpdActive READ isIpdActive WRITE setIsIpdActive NOTIFY isIpdActiveChanged)
    Q_PROPERTY(bool isVfdActive READ isVfdActive WRITE setIsVfdActive NOTIFY isVfdActiveChanged)
public:

    enum AlgType {
        Alg_IPD = 11,
        Alg_VFD = 12,
        Alg_PFR = 13,
    };

    static AlgServer* _instance;
    static QObject* qml_singleton_provider(QQmlEngine *qmlEngine,QJSEngine *jsEngine)
    {
        Q_UNUSED(qmlEngine);
        Q_UNUSED(jsEngine);
        return _instance = new AlgServer();
    }
    bool isIpdActive() const;
    bool isVfdActive() const;

signals:
    void isIpdActiveChanged(bool isIpdActive);
    void isVfdActiveChanged(bool isVfdActive);

    void sig_alg_test_data(const QString& message);
    void sig_alg_ipd_data(const QString& message);
    void sig_alg_vfd_data(const QString& message);



public slots:
    void setVideoFrame(const QVideoFrame& frame);

    void add_ipd_processor();
    void setIsIpdActive(bool isIpdActive);
    void push_ipd_videoFrame(const QVideoFrame& frame);

    void add_vfd_processor();
    void setIsVfdActive(bool isVfdActive);
    void push_vfd_videoFrame(const QVideoFrame& frame);








private:
    explicit AlgServer(QObject *parent = 0);

    IPDProcessor* m_ptr_ipd_processor;
    VFDProcessor* m_ptr_vfd_processor;
    bool m_is_processor_init;
    bool m_isIpdActive;
    bool m_isVfdActive;
};

Q_DECLARE_METATYPE(AlgServer::AlgType) //通过Q_DECLARE_METATYPE声明后，就可以让自定义的类型设置到QVariant
#endif // ALG_SERVER_H
