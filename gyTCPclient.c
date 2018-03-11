/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Name: C Command line chat client       
 * Program: gyTCPclient.c
 * Auther: Guo Yang <guoyang@webmail.hzau.edu.cn>
 * Version: 0.0.2
 * Date(mm/dd/yyyy): 3/10/2018
 * Description: 
 *  client program for my TCP command line chat program
 *  
 * References:
 *      1. http://blog.csdn.net/jackychu/article/details/4461927
 * 
 * History:
 *  1. 12/11/2017 guoyang
 *      first edit, gcc-7.1.0 + macOS 10.12.6
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

# include <unistd.h>          
# include <stdio.h>
# include <string.h>
# include <stdlib.h> 
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# define IP_ADDRESS "127.0.0.1" // For testing purpose, can be altered to user input.
# define PORT 4444 // Port is set to 4444 for testing purpose, can be altered to user input.
# define BUFFSIZE 256 // 256B are max capacity for both client and server msg.

int main()
{ 
	int sock;  
	struct sockaddr_in client_connection; 

	char client_msg_buffer[BUFFSIZE]; 
	char server_msg_buffer[BUFFSIZE];
    // printf("%d\n",sizeof(server_msg_buffer));

	printf("Client is up now and socket connection is established.\n");

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) { 
		perror ("Error opening channel");
		close(sock);
		exit(1);
	}

    // filling up sockaddr_in
	bzero(&client_connection, sizeof(client_connection)); 
	client_connection.sin_family = AF_INET; 
	client_connection.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
	client_connection.sin_port = htons(PORT); 

    // convert sockaddr_in to struct sockaddr
	if (connect(sock, (struct sockaddr *)&client_connection, sizeof(client_connection)) < 0) { 
		perror ("Error establishing communications");
		close(sock);
		exit(1);
	}

	while (1) {   
		printf(">> ");// start input prompt
        // client start inputing
		gets(client_msg_buffer);
		write(sock, client_msg_buffer, BUFFSIZE);
        // client inputs 'bye' indicates exiting program
		if ((client_msg_buffer[0] == 'b' || client_msg_buffer[0] == 'B') && 
            (client_msg_buffer[1] == 'y' || client_msg_buffer[1] == 'Y') && 
            (client_msg_buffer[2] == 'e' || client_msg_buffer[2] == 'E')) {
			    break;
		}
		read(sock, server_msg_buffer, BUFFSIZE);
		printf("Server>> msg received: [%s] .\n", server_msg_buffer);
        
        // server inputs 'bye' indicates exiting program
        if ((server_msg_buffer[0] == 'b' || server_msg_buffer[0] == 'B') && 
            (server_msg_buffer[1] == 'y' || server_msg_buffer[1] == 'Y') && 
            (server_msg_buffer[2] == 'e' || server_msg_buffer[2] == 'E')){
                printf("Server exited...your session will be closed now...\n");
			    break;
		}	
	}

	printf("Client Exiting now.\n");
    
    // clean up
	close(sock); 
	exit(0); 
} 
