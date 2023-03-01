/*	Motivation: build a set of file descriptors we're interested in.
	Call a function that will return if any of the file descriptors are ready for I/O,
	or throw out a time-out.*/

/*	int select(int nfds, fd_set* restrict readfds, fd_set* restrict writefds,
				fd_set* restrict exceptfds, struct timeval* restrict timeout)
	
	- nfds: nfds: number of fds.
	- fd_set* check if any of file descriptors in those sets are ready for reading,
	  writing, or if an exceptional condition has occurred.
	- timeout: how long we wan to wait (NULL forever or 0 no wait at all)	

	Returns: # of descriptors if ok, -1 otherwise.

*/
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 256
#define SERVER_BACKLOG 3 // max queue length of socket pending connections
#define SERVER_PORT 9000

#define NUM_CLIENTS 5

int main()
{ 
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		perror("setting the socket descriptor");
		return EXIT_FAILURE;
	}

	struct sockaddr_in srvAddr; 
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = INADDR_ANY; // server reachable by any of its interfaces
	srvAddr.sin_port = htons(SERVER_PORT);

	if( bind(sockfd , (struct sockaddr*) &srvAddr,  sizeof(srvAddr)) < 0) {
		perror("binding the socket descriptor with server address");
		return EXIT_FAILURE;
	}

	if( listen(sockfd, SERVER_BACKLOG) < 0) {
		perror("setting the socket to accept incoming requests");
		return EXIT_FAILURE;
	}

	int addrlen = sizeof(srvAddr);

	printf("Waiting for incoming client requests...");

    fd_set readfds; // set of socket descriptors

    int maxsd;

    int clientfd[NUM_CLIENTS];
    memset(clientfd, 0, sizeof(int) * NUM_CLIENTS);

	char buffer[1025];  //data buffer of 1K 

  	//a message 
    char *message = "ECHO Daemon v1.0 \r\n";  

	while(1)
	{
		FD_ZERO(&readfds); //clear the socket set

        FD_SET(sockfd, &readfds);
        maxsd = sockfd; 

        int i, sd;
        for( i = 0 ; i < NUM_CLIENTS; i++)
        {
        	sd = clientfd[i];

        	if(sd > 0)
        		FD_SET(sd, &readfds); // add clientfd[i] to read list
        	maxsd = sd > maxsd ? sd : maxsd; // keep track of highest-valued descriptor
        }

        int activity = select( maxsd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))  
            printf("select error");

        /* If something happened on the master socket, then its an incoming connection */
    	if (FD_ISSET(sockfd, &readfds))
    	{
    		int newfd = accept(sockfd, (struct sockaddr*) &srvAddr, (socklen_t*)&addrlen);
			if(newfd < 0) {
				perror("accepting incoming request");
				return EXIT_FAILURE;
			}

			//inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd: %d , ip is : %s , port : %d\n", newfd, inet_ntoa(srvAddr.sin_addr) , ntohs(srvAddr.sin_port));

			//send new connection greeting message 
            if( send(newfd, message, strlen(message), 0) != strlen(message) )  
                perror("send");
                 
            puts("Welcome message sent successfully");  
                 
            //add new socket to array of sockets 
            for (i = 0; i < NUM_CLIENTS; i++)  
            {  
                //if position is empty 
                if( clientfd[i] == 0 )  
                {  
                    clientfd[i] = newfd;  
                    printf("Adding to list of sockets as %d\n" , i);  
                    break;  
                }  
            }  
        } 

        //else its some IO operation on some other socket
        for (i = 0; i < NUM_CLIENTS; i++)  
        {  
            sd = clientfd[i];  
                 
            if (FD_ISSET( sd , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message 
                int valread = 0;
                if ((valread = read( sd , buffer, 1024)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&srvAddr, \
                        (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" , 
                          inet_ntoa(srvAddr.sin_addr) , ntohs(srvAddr.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    clientfd[i] = 0;  
                }  
                     
                //Echo back the message that came in 
                else 
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    buffer[valread] = '\0';  
                    send(sd , buffer , strlen(buffer) , 0 );  
                }  
            }  
        }  
   	}
 
   	return 0;
}

