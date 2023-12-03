
#include "header.h"

int main(int argc,char** argv)
{

	if(argc!=2)
	{
		fprintf(stderr,"Incorrect arguments count !! Enter the port number\n");
		exit(1);
	}
	else
	{
    		int port = atoi(argv[1]);
    
    		uint8_t socket_desc;
    		struct sockaddr_in server_addr;
    		char client_message[MAX];

  		memset(client_message,'\0',sizeof(client_message));  // Clean buffers

    		socket_desc = socket(AF_INET, SOCK_STREAM, 0);   // Create socket

    		if(socket_desc < 0)
    		{
        		perror("\033[1;31m[-] Unable to create socket \033[1;0m\n");
        		return -1;
    		}

    		printf("\n\033[1;32m[+] Socket created successfully... \n\033[1;0m");

    // Set port and IP the same as server-side:
    		server_addr.sin_family = AF_INET;
    		server_addr.sin_port = htons(port);
    		server_addr.sin_addr.s_addr = inet_addr("192.168.1.122");


    // Send connection request to server:
    		
    		if( connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))< 0)
    		{
        		perror("\033[1;31m[-] Unable to connect to the server \033[1;0m\n");
        		return -1;
    		}
    		printf("\033[1;32m[+] Connection established...\033[1;0m\n");

  //creating a thread
  		pthread_t thread;
  		pthread_create(&thread, NULL, Msg_Receving, (void*) &socket_desc);

  		printf("\n\n....... YOU CAN SEND MESSAGE TO SERVER NOW ....... \n");

    		while(1)
    		{
    			memset(client_message,'\0', sizeof(client_message));

    			gets(client_message);  // Get input from the user

    			if(strcmp(client_message, "EXIT")==0)
    			{
      // Send the message to server:
      				if(send(socket_desc, client_message, strlen(client_message), 0) < 0)
      				{
        				perror("\033[1;31m[--] Unable to send message \033[1;0m\n");
        				return -1;
      				}
      				printf(" \n\n\033[1;31m[X] you have been exited...\033[1;0m\n");
      				break;
    			}
    			else
    			{
      // Send the message to server:
      				if(send(socket_desc, client_message, strlen(client_message), 0) < 0)
      				{
        				perror("\033[1;31m[--] Unable to send message\033[1;0m\n");
        				return -1;
      				}
    			}	
    		}

    // Close the socket:
    		close(socket_desc);
  		printf("\033[1;31m[X] Socket is been closed... \033[1;0m\n");
  	}
    	return 0;
}
