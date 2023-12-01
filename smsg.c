
#include "header.h"

// Creatinng clint count global variable to check no of clients
extern int clientCount;

char output[MAX];
// Declare and initializing pthread_t type variable and struct client variable for use
extern struct client Client[10];
extern pthread_t thread[10];


void message(void* ClientDetail,char* clientMsg)
{
struct client* clientDetail = (struct client*) ClientDetail;
int index = clientDetail -> index;
  int clientSocket = clientDetail -> socketID;

// separating client id
      char *sep;
      sep = strtok(clientMsg, ":");

      // sep holds in the first token now check if the first token is contain number or not
      int isDigit = 1;
      for(int i = 0; i < strlen(sep); i++){
        if(isdigit(sep[i]) == 0){
          isDigit = 0;
        }
      }

      // Convert client id from char to int
      int id;

      if(isDigit){
        id = atoi(sep) - 1;

        // getting the message token part
        sep = strtok(NULL, ":");

        //if client is active then send msg otherwise send reciver client is not active to sender client
        if(strcmp(Client[id].status ,"ACTIVE") == 0 && sep){

          //sending the message to that client 
          //int l = 0;
           sprintf(output, "[msg] From Client %d : %s", index+1, sep);

    
          if(send(Client[id].socketID, output, strlen(output), 0) < 0){
            printf("[--] Can't send message...\n");
          }

          // server response to the client for sending message successfully
  
          memset(output,'\0',sizeof(output));
          sprintf(output, "[res] Message sent to client %d...\n", id+1);

          printf(" ..... Successfully send the message to client %d from client %d .....\n", id+1, index+1);
        }
        else{
          sprintf(output, "[res] Cannot send the message since client %d is DE-ACTIVE...\n", id+1);
        }
      }
      else{
        strcpy(output, "[res] WRONG CLIENT ID...\n");
      }

      if(send(clientSocket, output, strlen(output), 0) < 0){
      printf("[--] Can't send message...\n");
    }
    }
