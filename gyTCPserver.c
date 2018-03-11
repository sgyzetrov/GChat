/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Name: C Command line chat server       
 * Program: gyTCPserver.c
 * Auther: Guo Yang <guoyang@webmail.hzau.edu.cn>
 * Version: 0.0.2
 * Date(mm/dd/yyyy): 3/11/2018
 * Description: 
 *  server program for my TCP command line chat program
 *  
 * References:
 *      1. http://blog.csdn.net/jackychu/article/details/4461927
 * 
 * History:
 *  1. 12/11/2017 guoyang
 *      first edit, gcc-7.1.0 + macOS 10.12.6
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

# include <sys/types.h>
# include <unistd.h>          
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>     
# include <sys/socket.h>
# include <sys/un.h>
# include <netinet/in.h>

# define PORT 4444 // Port is set to 4444 for testing purpose, can be altered to user input.
# define BUFFSIZE 256 // 256B are max capacity for both client and server msg.

void clean_up(int cond, int *sock)
{ 
	printf("Finishing up, Socket Exited.\n");
	close(*sock); 
	exit(cond);
} 

int main()
{ 
	int sock; 
	int connect_sock; 
	struct sockaddr_in server_connection; 
	unsigned int len; 

    
	char client_msg_buffer[BUFFSIZE];
	char server_msg_buffer[BUFFSIZE];
	sock = socket(AF_INET, SOCK_STREAM, 0);  
	if (sock < 0) { 
		perror ("Error opening channel");
		clean_up(1, &sock);
	}

	bzero(&server_connection, sizeof(server_connection)); 
	server_connection.sin_family = AF_INET;                                   
	server_connection.sin_port = htons(PORT); 
	server_connection.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (struct sockaddr *)&server_connection, sizeof(server_connection)) < 0) { 
		perror ("Error naming channel");
		clean_up(1, &sock);
	}

	printf("Server is up and waiting for socket connection from client.\n");
	listen(sock, 1); 
	len = sizeof(server_connection);
	connect_sock = accept(sock, (struct sockaddr *)&server_connection, &len);



	while (1) { 
        // read client's input
		read(connect_sock, client_msg_buffer, BUFFSIZE);
		printf("Client>> msg received: [%s] .\n", client_msg_buffer);
        if ((client_msg_buffer[0] == 'b' || client_msg_buffer[0] == 'B') && 
            (client_msg_buffer[1] == 'y' || client_msg_buffer[1] == 'Y') && 
            (client_msg_buffer[2] == 'e' || client_msg_buffer[2] == 'E')) {
                printf("Client exited...waiting for another socket connection from client.\n");
                listen(sock, 1);
                len = sizeof(server_connection);
	            connect_sock = accept(sock, (struct sockaddr *)&server_connection, &len);
                read(connect_sock, client_msg_buffer, BUFFSIZE);
		        printf("Client>> msg received: [%s] .\n", client_msg_buffer);
		}

		printf(">> ");// start input prompt
        // server inputting
		gets(server_msg_buffer);
		write(connect_sock, server_msg_buffer, BUFFSIZE);
        // server inputs 'bye' indicates exiting program
		if ((server_msg_buffer[0] == 'b' || server_msg_buffer[0] == 'B') && 
            (server_msg_buffer[1] == 'y' || server_msg_buffer[1] == 'Y') && 
            (server_msg_buffer[2] == 'e' || server_msg_buffer[2] == 'E')){
			    break;
		}	
	}

    printf("Server Exiting now.\n");

	close(connect_sock); 
	clean_up(0, &sock); 
}
