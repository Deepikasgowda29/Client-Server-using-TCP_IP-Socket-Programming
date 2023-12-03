#include"header.h"

void * Msg_Receving(void* socketID)
{
  	uint8_t sock_fd = *((int*) socketID);
  	char server_message[MAX] ;

  	while(1)
  	{
    		memset(server_message,'\0',sizeof(server_message));

    // Receive the server's response:
    		if(recv(sock_fd, server_message, sizeof(server_message), 0) < 0)
    		{
      			perror("\033[1;31m[--] Error while receiving server's msg \033[1;0m\n");
      			break;
    		}

    		printf("%s\n",server_message);   // printing the message
  	}
  
  	printf("\n\033[1;31m[X] Connection closed ...\033[1;0m\n");
  	pthread_exit(NULL);
}
