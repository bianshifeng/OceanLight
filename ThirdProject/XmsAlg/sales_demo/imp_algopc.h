#ifndef IMP_ALGOPC_H
#define IMP_ALGOPC_H

#include <QObject>
#include <QThread>
#include <QDebug>

#include "IMP_Socket.h"
#include "IMP_AlgoResQueue.h"


#define RECV_VIDEO_RESPONSE_LEN         1000
#define VIDEO_FRAME_HEAD_INFO_SIZE      1000
#define RECV_VIDEO_STREAM_BUF_LEN       0x100000
class IMP_AlgoPC : public QThread
{
    Q_OBJECT
public:
    IMP_AlgoPC(QObject *parent = 0):QThread(parent){}
    void run();
    void stop();

public slots:
    ///获取IP地址和端口号
    void setIPAddressPort(QString strIPAddress, int nVideoPort, int nAlgorithmPort);
public:
    void set_alg_rlt_queue(IMP_AlgoResQueue* alg_rlt_queue);

private:
    void _push_alg_rlt(char *rlt, int rlt_len, int frame_no);
private:
    char *m_rlt;
    int m_rlt_len;

    IMP_AlgoResQueue* m_alg_rlt_queue;
    int m_nRunFlag;

    int m_nVideoPort;
    int m_nAlgoPort;
    QString m_strDeviceIP;
};

#endif // IMP_ALGOPC_H
