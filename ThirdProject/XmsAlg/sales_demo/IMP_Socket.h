#ifndef IMP_SOCKET_H
#define IMP_SOCKET_H

#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <WinSock.h>

#pragma comment(lib,"ws2_32.lib")

SOCKET SocketInit(char* IP_ADDRESS, int PORT);

/** not used, replace by livex_socket.cpp livex_recv */
int SocketRecv(SOCKET SocketClient, char* data, int len, int flags);

/** not used, replace by livex_socket.cpp livex_send */
int SocketSend(SOCKET SocketClient, char* data, int len, int flags);

int SocketClose(SOCKET SocketClient);

#endif // IMP_SOCKET_H
