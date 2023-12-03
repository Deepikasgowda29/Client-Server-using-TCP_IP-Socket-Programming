
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX 2000

//macros for emoji unicodes
//1f44d
#define LAUGH "\U0001f602"
#define SMILE "\U0001f60a"
#define HEART "\U00002764"
#define ANGRY "\U0001f621"
#define OK "\U0001f44d"


struct client{
  int index;
  int socketID;
  struct sockaddr_in client_addr;
  int len;
  char status[20];
};


void * Command(void * ClientDetail);

void message(void* ClientDetail,char* clientMsg);

char* replaceWord(char* s,char* oldW, char* newW); 

void * Msg_Receving(void* socketID);
