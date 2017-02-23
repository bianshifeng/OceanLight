#include "imp_algopc.h"
#include "imp_cpc_para.h"
#include "livex_socket.h"
typedef struct targets
 {
     int length;
     int seq;
     IMP_CPC_Result_S target;
 } TS;
void IMP_AlgoPC::run()
{
    qDebug() << QStringLiteral("启动Recv Alg Stream线程Id:") << (int)QThread::currentThreadId();
    SOCKET SocketClient = SocketInit(m_strDeviceIP.toLocal8Bit().data(), m_nAlgoPort);
    qDebug()<<"Socket Client ID is: " << SocketClient;
    if(SocketClient < 0) {
        return;
    }

    m_nRunFlag = 1;

    TS alg_result;

    while(m_nRunFlag)
    {
        if(livex_recv(SocketClient, (char*)(&alg_result), sizeof(TS), 0) < 0){
            qDebug("ALg Client Recieve Alg result Failed!!!");
            break;
        }
        /*
        if(alg_result.target.u32TgtNum>0){
            qDebug()<<"-------------alg_result.target.u32TgtNum:"<<alg_result.target.u32TgtNum;
            qDebug()<<"-------------------------------------------";
            qDebug()<<"-------------------------------------------";
            qDebug()<<"-------------------------------------------";
            qDebug()<<"-------------------------------------------";
            qDebug()<<"-------------------------------------------";
        }
        */
        _push_alg_rlt((char*)(&alg_result.target), sizeof(TS), alg_result.seq);
    }

    qDebug() << QStringLiteral("Recv Alg");

    this->quit();
}

///获取IP地址和端口号
void IMP_AlgoPC::setIPAddressPort(QString strIPAddress, int nVideoPort, int nAlgorithmPort)
{
    m_nVideoPort        = nVideoPort;
    m_nAlgoPort         = nAlgorithmPort;
    m_strDeviceIP       = strIPAddress;
}

void IMP_AlgoPC::stop()
{
    m_nRunFlag = false;
}

void IMP_AlgoPC::set_alg_rlt_queue(IMP_AlgoResQueue* alg_rlt_queue)
{
    m_alg_rlt_queue = alg_rlt_queue;
}

void IMP_AlgoPC::_push_alg_rlt(char *rlt, int rlt_len, int frame_no)
{
    IMP_AlgoRes *free_node = m_alg_rlt_queue->GetAlgoResAddr();
    if(!free_node) return;
    free_node->nFrameNo = frame_no;
    memcpy(free_node->pResult, rlt, rlt_len);
}

