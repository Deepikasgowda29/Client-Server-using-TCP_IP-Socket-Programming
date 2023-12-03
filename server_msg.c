
#include "header.h"

//extern uint8_t clientCount;

char output[MAX];
extern struct client Client[10];

void message(void* ClientDetail,char* clientMsg)
{
	struct client* clientDetail = (struct client*) ClientDetail;
	uint8_t index = clientDetail -> index;
  	uint8_t clientSocket = clientDetail -> socketID;

// separating client id
	char *sep;
	sep = strtok(clientMsg, ":");     // sep holds in the first token now check if the first token is contain number or not
	
      	bool isDigit = 1;
      	for(int i = 0; i < strlen(sep); i++)
      	{
        	if(isdigit(sep[i]) == 0)
        	{
          		isDigit = 0;
        	}
      	}

// If token is digit
      
      	if(isDigit)
      	{
      		uint8_t id;
        	id = atoi(sep) - 1;  //convert string token to int
        	sep = strtok(NULL, ":");   // getting the message token part
        
        	char *emoji[] = {"LAUGH","HEART","SMILE","ANGRY","OK"};
		char *unicode[] = {LAUGH,HEART,SMILE,ANGRY,OK};
	
		for(int i=0;i<5;i++)
		{
			sep = replaceWord(sep,emoji[i],unicode[i]);  //for replacing the message for emoji unicode
		}
	
//if client is active then send msg otherwise send reciver client is not active to sender client
        	if(strcmp(Client[id].status ,"ACTIVE") == 0 && sep)
        	{ 
           		sprintf(output, "\n\033[1;32m[msg] From Client %d : %s\033[1;0m\n", index+1, sep);  //sending the message to that client

          		if(send(Client[id].socketID, output, strlen(output), 0) < 0)
          		{
            			perror("\033[1;31m[--] Can't send message...\033[1;0m\n");
          		}
  
          		memset(output,'\0',sizeof(output));
          		sprintf(output, "\n\033[1;34m[res] Message sent to client %d...\033[1;0m\n", id+1);  // server response to the client
			printf("\033[1;32m ..... Successfully send the message to client %d from client %d .....\033[1;0m\n", id+1, index+1);
        	}
 
        	else
        	{
          		sprintf(output, "\n\033[1;31m[res] Cannot send the message since client %d is DE-ACTIVE...\033[1;0m\n", id+1);
        	}
      	}
      	
// If token is not digit      	
      	else
      	{
        	strcpy(output, "\n\033[1;31m[res] WRONG CLIENT ID...\033[1;0m\n");
      	}

      	if(send(clientSocket, output, strlen(output), 0) < 0)
      	{
      		perror("\033[1;31m[--] Can't send message...\033[1;0m\n");
    	}
}
