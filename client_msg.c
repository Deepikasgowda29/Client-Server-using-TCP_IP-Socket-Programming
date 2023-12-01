#include"server.h"

void * doReceving(void* socketID){
  int fd = *((int*) socketID);
  char server_message[MAX] ;

  while(1){
    memset(server_message,'\0',sizeof(server_message));

    // Receive the server's response:
    if(recv(fd, server_message, sizeof(server_message), 0) < 0){
      printf("\033[1;31m [--] Error while receiving server's msg \033[0m\n");
      break;
    }

    // printing the message
    printf("%s\n",server_message);
  }

  printf("[X] Connection closed ...\n");
  pthread_exit(NULL);
}
