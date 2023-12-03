
#include "header.h"

extern uint8_t clientCount;
extern struct client Client[3];

void* Command(void * ClientDetail)
{
  // Type casting ClientDetail to (struct clint *) type from (void *)
  	struct client* clientDetail = (struct client*) ClientDetail;
  
  	FILE *fp;  //file to save the history of messages and commands received in server
  	fp = fopen("history.txt","a");
  	if(fp==NULL)
  	{
  		printf("\nMy file did not open\n");
  	}

  // Getting client index and socket id
  	uint8_t index = clientDetail -> index;
  	uint8_t clientSocket = clientDetail -> socketID;

  	printf("\n\033[1;32m[++] Client %d connected... \033[1;0m\n", index+1);

  // sending the server Basic command Codes for CLIENT GUIDE
  	char output[MAX];
  	char basicCommand[MAX] = "\n\033[1;36m... [SERVER-COMMANDS-GUIDE] ...\n\n--> 'LIST'\t:- to get clients list and status\n--> 'EXIT'\t:- to end the connection\n--> 'HELP'\t:- to get command list\n\n--> '<client id> : <message>'\t:- to send message\n\n--> To send Emojis type : [ \U00002764 : HEART ] [ \U0001f602 : LAUGH ] [ \U0001f60a : SMILE ] [ \U0001f621 : ANGRY ] [ \U0001f44d : OK ]\n\n---------------------------------------------------------------------------------------------------\033[1;0m\n";
  	char buffer[MAX];

  	memset(output,'\0',sizeof(output));
  	strcpy(output, basicCommand);
  	if(send(clientSocket, output, strlen(output), 0) < 0)
  	{
    		perror("\033[1;31m[--] Can't send message... \033[1;0m\n");
    		return NULL;
  	}
  // Message processing
  	while(1)
  	{
    		char clientMsg[MAX];
    		bool CHAT = 0;

    		memset(clientMsg,'\0',sizeof(clientMsg));  //clearing the buffers
    		memset(output,'\0',sizeof(output));

    // receving client message
    		if(recv(clientSocket, clientMsg, sizeof(clientMsg), 0) < 0)
    		{
      			perror("\033[1;31m[--] Couldn't receive client message... \033[1;0m\n");
      			break;
    		}
    		fprintf(fp,"\n+++ CLIENT %d | client message : %s | client socket : %d\n",index+1, clientMsg, clientSocket);
    		printf("\n+++ CLIENT %d | client message : %s | client socket : %d\n",index+1, clientMsg, clientSocket);

    //if the message contains ':' delemeter then set CHAT = true;
    		char *ck;
    		ck = strchr(clientMsg,':');
    		if(ck!=NULL)
    		{
      			CHAT = 1;
    		}
 
    // user commands and actions
    		if(strcmp(clientMsg, "EXIT") == 0)
    		{
      			break;
    		}
    		else if(strcmp(clientMsg, "HELP") == 0)
    		{
      			strcpy(output, basicCommand);
    		}
    		else if(strcmp(clientMsg, "LIST") == 0)
    		{
      			int len = 0;
      			if(clientCount == 1)
      			{
        			len += sprintf(output + len, "\033[1;34m[res] Currently no other clients are connected...\033[1;0m\n");
      			}
      			else
      			{
        			for(int i = 0; i < clientCount; i++)
        			{
          				if(i != index)
          				{
            					len += sprintf(output + len, "\033[1;34m[res] Client: %d | soket: %d | status : %s\033[1;0m\n",(i+1), Client[i].socketID, Client[i].status);	// sprintf returns the no of bytes that are written in array which is held by variable l
                                                                                // so to append multiple sentance we need to increment output to l byte for getting that location
          				}
        			}
      			}
    		}
  		else if(CHAT)
  		{
	 		message(clientDetail,clientMsg);
    		}
    
    // wrong command response
    
    		else
    		{
      			strcpy(output, "\n\033[1;31m[res] WRONG INPUT COMMAND... PLEASE TRY AGAIN WITH VALID COMMAND...\033[1;0m\n");
    		}
    

    //sending servers response to this client
    		if(send(clientSocket, output, strlen(output), 0) < 0)
    		{
      			perror("\n\033[1;31m[--] Can't send message... \033[1;0m\n");
      			break;
    		}

  	}

  // making this client status DE-ACTIVE and closing its socket
  	stpcpy(clientDetail->status,"\033[1;31mDE_ACTIVE\033[1;0m");
  	close(clientSocket);
  	printf("\n\033[1;31m[...] Client %d Exited...Thread id = %u \033[1;0m\n\n",index + 1, (unsigned int)pthread_self());
  	return NULL;
}
