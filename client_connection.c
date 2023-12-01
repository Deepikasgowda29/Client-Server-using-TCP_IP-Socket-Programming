
#include "header.h"

int main(int argc,char** argv)
{
    int port = atoi(argv[1]);

    int socket_desc;
    struct sockaddr_in server_addr;
    char client_message[MAX];

    // Clean buffers:
  memset(client_message,'\0',sizeof(client_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc < 0){
        printf("[-] Unable to create socket \n");
        return -1;
    }

    printf("\n [+] Socket created successfully... n");

    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    // Send connection request to server:
    int a = connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if( a< 0){
        printf("[-] Unable to connect to the server \n");
        return -1;
    }
    printf("[+] Connection established...%d n",a);

  //creating a thread
  pthread_t thread;
  pthread_create(&thread, NULL, doReceving, (void*) &socket_desc);

  printf("\n\n....... YOU CAN SEND MESSAGE TO SERVER NOW ....... \n");

    while(1){
    memset(client_message,'\0', sizeof(client_message));

    // Get input from the user:
    gets(client_message);

    if(strcmp(client_message, "EXIT")==0){
      // Send the message to server:
      if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
        printf("[--] Unable to send message \n");
        return -1;
      }
      printf(" \n\n[X] you have been exited...\n");
      break;
    }
    else{
      // Send the message to server:
      if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
        printf("[--] Unable to send message\n");
        return -1;
      }
    }
    }

    // Close the socket:
    close(socket_desc);
  printf("[X] Socket is been closed... n\n");

    return 0;
}
