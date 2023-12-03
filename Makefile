cc = gcc
TARGET1 = server
TARGET2 = client
FLAG = -o

all:		server_connection.o server_msg.o command.o client_connection.o client_msg.o  replaceString.o 
		$(cc) server_connection.o server_msg.o command.o replaceString.o  $(FLAG) $(TARGET1)
		$(cc) client_connection.o client_msg.o  $(FLAG) $(TARGET2)
	
server_connection.o: server_connection.c header.h
		$(cc) -c server_connection.c
		
server_msg.o:	     server_msg.c header.h
		$(cc) -c server_msg.c
		
		
command.o:	     command.c header.h
		$(cc) -c command.c
		
client_connection.o: client_connection.c header.h
		$(cc) -c client_connection.c
		
		
client_msg.o: 	     client_msg.c header.h
		$(cc) -c client_msg.c
		
replaceString.o:     replaceString.c header.h
		$(cc) -c replaceString.c
				
clean:	      
		rm $(TARGET1) $(TARGET2) *.txt *.o
