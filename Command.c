
#include "header.h"

// Creatinng clint count global variable to check no of clients
extern int clientCount;

// Declare and initializing struct client variable
// for use
extern struct client Client[3];

void *Command(void *ClientDetail) 
{
  	// Type casting ClientDetail to (struct clint *) type from (void *)
  	struct client *clientDetail = (struct client *)ClientDetail;

  	FILE *fp;
  	fp = fopen("history.txt", "a");
  	if (fp == NULL) 
  	{
     		perror("\nMy file did not open\n");
  	}

  	// Getting client index and socket id
  	uint8_t index = clientDetail->index;
  	uint8_t clientSocket = clientDetail->socketID;

  	printf("[++] Client %d connected... \n", index + 1);

  	// sending the server Basic command Codes for CLIENT GUIDE
  	char output[MAX];
  	char basicCommand[MAX] =
      				"\n... [SERVER-COMMANDS-GUIDE] ...\n\n--> 'LIST'\t:- to get clients list "
      				"and status\n--> 'EXIT'\t:- to end the connection\n--> 'HELP'\t:- to get "
      				"command list\n\n--> '<client id> : <message>'\t:- to send "
      				"message\n\n-------------------------------\n";
  	char buffer[MAX];

  	memset(output, '\0', sizeof(output));
  	strcpy(output, basicCommand);
  	if (send(clientSocket, output, strlen(output), 0) < 0) 
  	{
    		perror(" [--] Can't send message... \n");
    		return NULL;
  	}
  	// Message processing
  	while (1) 
	{
    		char clientMsg[MAX];
    		bool CHAT = 0;

    		// clearing the buffers

    		memset(clientMsg, '\0', sizeof(clientMsg));
    		memset(output, '\0', sizeof(output));

    		// receving client message
    		if (recv(clientSocket, clientMsg, sizeof(clientMsg), 0) < 0) 
    		{
      			perror(" [--] Couldn't receive client message... \n");
      			break;
    		}
    		fprintf(fp, "\n+++ CLIENT %d | client message : %s | client socket : %d\n",
            	index + 1, clientMsg, clientSocket);
    		printf("\n+++ CLIENT %d | client message : %s | client socket : %d\n",index + 1, clientMsg, clientSocket);

    		// if the message contains ':' delemeter then set CHAT = true(1);
    		char *ck;
    		ck = strchr(clientMsg, ':');
    		if (ck != NULL) 
    		{
      			CHAT = 1;
    		}

    		// user commands and actions
    		if (strcmp(clientMsg, "EXIT") == 0) 
    		{
      			break;
    		} 
    		else if (strcmp(clientMsg, "HELP") == 0) 
    		{
      			strcpy(output, basicCommand);
    		} 
    			
    		else if (strcmp(clientMsg, "LIST") == 0) 
    		{
      			int8_t len = 0;
      			if (clientCount == 1) 
      			{
        			len += sprintf(output + len,"[res] Currently no other clients are connected...\n");
      			} 
      			else 
      			{
       				 for (int i = 0; i < clientCount; i++) 
       				 {
          				if (i != index) 
          				{
            					len += sprintf(output + len, "[res] Client: %d | soket: %d | status : %s\n",(i + 1),
            					Client[i].socketID,Client[i].status);       						
            					                // sprintf returns the no of bytes that are
                                   		// written in array which is held by variable
                                   		// len so to append multiple sentance we need
                                   		// to increment output to len byte for getting
                                   		// that location
          				}
        			 }
      			}
    		} 
    		else if (CHAT) 
    		{

      			message(clientDetail, clientMsg);
    		}

    		else 
    		{
      			// wrong command response
      			strcpy(output, "\n[res] WRONG INPUT COMMAND... PLEASE ENTER VALID COMMAND...\n");
    		}

    		// sending server response to this client
    		if (send(clientSocket, output, strlen(output), 0) < 0) 
    		{
      			perror("\n[--] Can't send message... \n");
      			break;
    		}
  	}

  // making this client status DE-ACTIVE and closing its socket
  strcpy(clientDetail->status, "DE_ACTIVE");
  close(clientSocket);
  printf("\n[...] Client %d Exited...Thread id = %u \n\n", index + 1,(unsigned int)pthread_self());
  return NULL;
}
