#ifndef _LIVEX_SOCKET_H
#define _LIVEX_SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

/*
  **return:-1 socket error, 0 time out, 1 send success
  */
int livex_send(int fd, const char *buf, int specified_len, int time_out);


/*
 *return:-1 error, 0 recv nothing, 1 recv success
 */
int livex_recv(int fd, char *buf, int specified_len, int time_out);

#ifdef __cplusplus
}
#endif

#endif
