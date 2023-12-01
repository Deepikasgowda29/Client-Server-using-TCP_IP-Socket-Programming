
#include "server.h"

// Creatinng client count global variable to check no of clients
int clientCount=0;

// Declare and initializing pthread_t type variable and struct client variable for use
struct client Client[3];
pthread_t thread[3];

int main(int argc,char** argv){
  // Creating the socket
  int sock_desc = socket(AF_INET, SOCK_STREAM, 0);
  if(sock_desc < 0){
    printf("[-] Error while creating the socket...\n");
    return -1;
  }
  printf("\n [+] Socket created successfully \n");
  int port = atoi(argv[1]);

  // Creating server_addr and setting its port and IP
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  // Bind to the set port and IP
  if( bind(sock_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 ){
    printf("[-] Couldn't bind to the port... \n");
    return -1;
  }
  printf(" [+] Done with binding... \n");

  // Listen for clients
  if( listen(sock_desc,3) < 0 ){
    printf(" [-] Cannot Listen... \n");
    return -1;
  }
  printf("[+] Listening for incoming connections...\n");

  // Accept an incoming connections
  while(clientCount < 3){
    Client[clientCount].socketID = accept(sock_desc, (struct sockaddr*)&Client[clientCount].client_addr, &Client[clientCount].len);
    Client[clientCount].index = clientCount;
    stpcpy(Client[clientCount].status,"ACTIVE");
    pthread_create(&thread[clientCount], NULL, ChattingProcess, (void*)&Client[clientCount]);
    clientCount++;
  }

  // pthread joining which waits for a thread to terminate, detaches the thread, then returns the thread exit status
  for(int i = 0; i < clientCount; i++){
    pthread_join(thread[i], NULL);
  }

  printf("\n\n---DONE---\n\n");
  //closing the socket
  close(sock_desc);
  //fclose(fp);
  return 0;
}
