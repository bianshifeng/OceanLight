#include <stdio.h>
#include <stdlib.h>
#include "livex_socket.h"


#include <sys/types.h>
#include <errno.h>
#include <string.h>

#ifdef WIN32
    #include <WinSock.h>
#else
    #include <unistd.h>
    #include <sys/ioctl.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <net/if.h>
#endif

#define _DEBUG

/**DEBUG()**/
#ifdef _DEBUG
  #define LVDEBUG(fmt, ...)  printf("%s %s, "__FILE__"[%d], DEBUG: "fmt, __DATE__, __TIME__, __LINE__, ##__VA_ARGS__);
#else
  #define LVDEBUG(fmt, ...)
#endif

/**ERROR()**/
#define LVERROR(fmt, ...)  printf("%s %s, "__FILE__"[%d], ERROR: "fmt, __DATE__, __TIME__, __LINE__, ##__VA_ARGS__);


/*
 **return:-1 socket error, 0 time out, 1 send success
 */
int livex_send(int fd, const char *buf, int specified_len, int time_out){
      fd_set fdR;
      struct timeval timeout;
      int  sended_len;

      if(specified_len <= 0){
          LVERROR("live socket: send(), specified_len is 0\r\n");
          return 1;
      }

      if(time_out <=0){
        time_out = 3600;
      }

      timeout.tv_sec = time_out;
      timeout.tv_usec = 0;
      
      sended_len = 0;
      while(1){
          int s;
          FD_ZERO(&fdR);
          FD_SET(fd, &fdR);
          timeout.tv_sec = time_out;
          timeout.tv_usec = 0;
          s = select(fd + 1, NULL, &fdR, NULL, &timeout);
          if(s == -1){
              break; 
          }else if(s == 0){
              return -1;
          }else if(FD_ISSET(fd, &fdR)){
              int sended_once_len = send(fd, buf + sended_len, specified_len - sended_len, 0);
              if(sended_once_len > 0){//success
                  sended_len += sended_once_len;
                  //printf("live socket: send return success, sended length this time:%d, now sended total length:%d\n", sended_once_len, sended_len);
                  FD_CLR(fd, &fdR);
                  if(sended_len == specified_len){
                      return 1;
                  }else if(sended_len < specified_len){
                      continue;
                  }else{
                      LVERROR("live socket: error! sended data lenght is more than specified lenght!");
                      return -1;
                  }
              }else if(sended_once_len == 0){//socket close
                 LVDEBUG("live socket: send return value is  0, socket was closed!\n");
                  return -1;
              }else if(sended_once_len == EINTR || sended_once_len == EAGAIN){//continue
                 LVDEBUG("live socket: send return value :EINTR || EAGAIN\n");
                  continue;
              }else{//socket error
                  LVERROR("live socket: error! send return error:%d\n", sended_once_len);
                  return -1;
              }
          }
  
      }//for
     
      return -1;
  }
  

/*
 *return:-1 error, 0 recv nothing, 1 recv success
 */
int livex_recv(int fd, char *buf, int specified_len, int time_out){
      fd_set fdR;
      struct timeval timeout;
      int  recvd_len;
      if(specified_len <= 0){
          LVDEBUG("live socket: recv(), specified_len is 0\n");
          return 1;
      }
      if(time_out <= 0){
        time_out = 100;
      }

      timeout.tv_sec = time_out;
      timeout.tv_usec = 0;

      recvd_len = 0;
      while(1){
          int s;
          FD_ZERO(&fdR);
          FD_SET(fd, &fdR);
          timeout.tv_sec = time_out;
          timeout.tv_usec = 0;
          s = select(fd + 1, &fdR, NULL, NULL, &timeout);
          if(s == -1){//error
              break;
          }else if(s == 0){//select time out
              return -1;
          }else if(FD_ISSET(fd, &fdR)){
              int recv_once_len = recv(fd, buf + recvd_len, specified_len - recvd_len, 0);
              if(recv_once_len > 0){
                  //printf("live socket: to recved length:%d, recvd length this time:%d\r\n", specified_len-recvd_len, recv_once_len);
                  recvd_len += recv_once_len;
                  //LVDEBUG("live socket: now recvd total length:%d\r\n", recvd_len);
                  FD_CLR(fd, &fdR);
                  if(recvd_len == specified_len){
                      return 1;
                  }else if(recvd_len < specified_len){
                      continue;
                  }else{
                      LVERROR("live socket: error! recvd data lenght is more than specified lenght!");
                      break;
                  }
              }else if(recv_once_len == EINTR || recv_once_len == EAGAIN){
                  LVDEBUG("live socket: recv return value :EINTR || EAGAIN\n");
                  continue;
              }else if(recv_once_len == 0){
                  LVDEBUG("live socket: recv return value is  0, socket was closed!\n");
                  break;
              }else{
                  LVDEBUG("live socket: error! recv return error:%d\n", recv_once_len);
                  break;
              }

          }
  
      }//while 1
      return -1;
}



  
