
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX 2000

//macros for emoji unicodes

#define LAUGH "\U0001f602"
#define SMILE "\U0001f600"
#define HEART "\U00002764"

struct client{
  int index;
  int socketID;
  struct sockaddr_in client_addr;
  int len;
  char status[20];
};


void * ChattingProcess(void * ClientDetail);

void message(void* ClientDetail,char* clientMsg);

char* replaceWord(char* s,char* oldW, char* newW); 

void * doReceving(void* socketID);
