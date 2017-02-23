#include "IMP_Socket.h"
#include <QDebug>

SOCKET SocketInit(char *IP_ADDRESS, int PORT) {
    SOCKET SocketClient;
    WSADATA Ws;
    //sockaddr_in ClientAddr;
    struct sockaddr_in ClientAddr;
    int nRet = 0;
    /* Init Windows Socket */
    if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 ) {
        qDebug("Init Windows Socket Failed::%d", GetLastError());
        return -1;
    }

    /* Create Socket */
    SocketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ( SocketClient == INVALID_SOCKET ) {
        qDebug("Create Socket Failed::%d", GetLastError());
        return -1;
    }

    ClientAddr.sin_family = AF_INET;
    //ClientAddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDRESS);

    ClientAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    ClientAddr.sin_port = htons(PORT);
    memset(ClientAddr.sin_zero, 0x00, 8);

    /* connect socket */
    nRet = connect(SocketClient,(struct sockaddr*)&ClientAddr, sizeof(ClientAddr));
    if ( nRet == SOCKET_ERROR ) {
        qDebug("Connect Error::%d", GetLastError());
        return -1;
    } else {
        qDebug("Connect succedded!");
    }
    return SocketClient;
}

/** not used, replace by livex_socket.cpp livex_recv */
int SocketRecv(SOCKET SocketClient, char* data, int len, int flags) {
    int nRecved = 0;
    int nRet = 0;
    do {
        nRet = recv(SocketClient, &data[nRecved], len - nRecved, flags);
        if(nRet>0) {
            nRecved += nRet;
        }
    }while(nRecved != len);
    return len;
}

/** not used, replace by livex_socket.cpp livex_send */
int SocketSend(SOCKET SocketClient, char* data, int len, int flags) {
    int nSended = 0;
    int nRet = 0;
    do {
        nRet = send(SocketClient, &data[nSended], len - nSended, flags);
        if(nRet>0) {
            nSended += nRet;
        }
    }while(nSended != len);
    return len;
}

int SocketClose(SOCKET SocketClient) {
    /* close socket */
    closesocket(SocketClient);
    WSACleanup();
    return 0;
}
