
#include "header.h"

// Creating client count global variable to check no of clients
uint8_t clientCount=0;

// Declare and initializing pthread_t type variable and struct client variable for use
struct client Client[3];
pthread_t thread[3];

int main(int argc,char** argv)
{

	if(argc!=2)
	{
		fprintf(stderr,"Incorrect arguments count !! Enter the port number\n");
		exit(1);
	}
	else
	{
  // Creating the socket
		uint8_t sock_desc = socket(AF_INET, SOCK_STREAM, 0);
		if(sock_desc < 0)
		{
    			perror("\033[1;31m[-] Error while creating the socket...\033[1;0m\n");
    			return -1;
  		}
  		printf("\n\033[1;32m[+] Socket created successfully \033[1;0m\n");
  		int port = atoi(argv[1]);

  // Creating server_addr and setting its port and IP
  		struct sockaddr_in server_addr;
  		server_addr.sin_family = AF_INET;
  		server_addr.sin_port = htons(port);
  		server_addr.sin_addr.s_addr = inet_addr("192.168.1.122");  //address of the server machine

  // Bind to the set port and IP
  		if( bind(sock_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 )
  		{
    			perror("\033[1;31m[-] Couldn't bind to the port...\033[1;0m \n");
    			return -1;
  		}
  		printf("\033[1;33m[+] Done with binding... \033[1;0m\n");

  // Listen for clients
  		if( listen(sock_desc,1) < 0 )
  		{
    			perror("\033[1;31m[-] Cannot Listen... \n\033[1;0m");
    			return -1;
  		}
  		printf("\033[1;33m[+] Listening for incoming connections...\033[1;0m\n");

  // Accept an incoming connections
  		while(clientCount < 3)
  		{
    			Client[clientCount].socketID = accept(sock_desc, (struct sockaddr*)&Client[clientCount].client_addr, &Client[clientCount].len);
    			Client[clientCount].index = clientCount;
    			strcpy(Client[clientCount].status,"ACTIVE");
    			pthread_create(&thread[clientCount], NULL, Command, (void*)&Client[clientCount]);
    			clientCount++;
  		}

  // pthread joining which waits for a thread to terminate, detaches the thread, then returns the thread exit status
  		for(int i = 0; i < clientCount; i++)
  		{
    			pthread_join(thread[i], NULL);
  		}

 		printf("\033[1;32m\n\n---DONE---\n\n\033[1;0m");
  
  		close(sock_desc);  //closing the socket
  	}
  	return 0;
}
