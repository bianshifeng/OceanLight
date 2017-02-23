#include "device_livex.h"
#include <QTcpSocket>
Device_LiveX::Device_LiveX(QObject *parent) : QObject(parent)
{

}

int Device_LiveX::livexSend(int fd, const char *cbuf, int specified_len, int time_out)
{
//    struct timeval t_timeOut;

//    int t_lenSended;

//    if(specified_len <= 0){
//        LVERROR("live socket: send(), specified_len is 0\r\n");
//        return 1;
//    }

//    if(time_out <=0){
//        time_out = 3600;
//    }


    QTcpSocket tcpSock;
    char* buf ="hello";
    tcpSock.connectToHost("59.64.159.87",7716);
    tcpSock.write(buf,strlen(buf)+1);
    if(tcpSock.waitForBytesWritten(3000))
       emit SockCondition("successful");
    else
       emit SockCondition("failed");
    tcpSock.disconnect();

    return 1;

}
