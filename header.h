
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 2000

struct client{
  int index;
  int socketID;
  struct sockaddr_in client_addr;
  int len;
  char status[20];
};


void * ChattingProcess(void * ClientDetail);

void message(void* ClientDetail,char* clientMsg);

void * doReceving(void* socketID);
