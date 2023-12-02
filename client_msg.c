#include"server.h"

void* Msg_Receving(void* Socket_id) // function to receive message from server
{
int socket_fd = *((int*) Socket_id); //pointer to assign value to socket file descriptor for communication
char server_msg[MAX]; //array to store received messages from server
 
while(1) 
{
//clean buffer
memset(server_msg,'\0',sizeof(server_msg));
 
//receving the server message
if(recv(socket_fd,server_msg,sizeof(server_msg),0)<0); //attempts to receive a message from the server using recv() function
{
perror("\n Error while receving the server message");
return -1; 
}
 
//printing the message
printf("%s\n",server_msg);
}
}
 
//creating a thread
pthread_t thread;
pthread_create(&thread, NULL,Msg_Receving, (void*), &socket_desc); //uses pthread_create() function to start execution of message receving function  in this new thread
printf("Now message can send to server\n");
 
while(1)
{
memset(client_message,'\0',sizeof(client_message)); //clears the client message buffer
gets(client_message); //reads user input
 
if(strcmp(client_message,"EXIT")==0)
{
 
//Sends the message to server
if(send(socket_desc, client_message, strlen(client_message),0)<0)
{
perror("Fails to send message\n");
return -1;
}
printf("you are exited\n");
break;
}
else{
// send message to server
if(send(socket_desc, client_message, strlen(client_message),0)<0){
perror("Fails to send message\n");
return -1;
}
}
