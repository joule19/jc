/* 	Simplest socket-based server implementation
 	that receives an incoming client message, and shutdowns thereafter */

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
#define SERVER_BACKLOG 1 // max queue length of socket pending connections
#define SERVER_PORT 9000

/* 	server flow:
	socket() -> bind() -> listen() -> accept() -> read() -> close() */

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

	/* bind() links the address specified by srvAddr to the
	   socket referred by sockfd */
	if( bind(sockfd , (struct sockaddr*) &srvAddr,  sizeof(srvAddr)) < 0) {
		perror("binding the socket descriptor with server address");
		return EXIT_FAILURE;
	}

	/*	listen() marks the socket referred to by sockfd as a passive socket
		in order to accept incoming requests using accept() */
	if( listen(sockfd, SERVER_BACKLOG) < 0) {
		perror("setting the socket to accept incoming requests");
		return EXIT_FAILURE;
	}

	int addrlen = sizeof(srvAddr);

	/* extracts the first connection request on the queue of pending connections for sockfd */
	int clientfd = accept(sockfd, (struct sockaddr*) &srvAddr, (socklen_t*)&addrlen);
	if(clientfd < 0) {
		perror("accepting incoming requests");
		return EXIT_FAILURE;
	}

	char buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);

	int cnt = read(clientfd, buf, BUFFER_SIZE);
	if(cnt < 0) 
		fprintf(stderr, "error reading symbols\n");
	else
		printf("%d symbols read.\n%s\n", cnt, buf);
	
	close(clientfd);
	shutdown(sockfd, SHUT_RDWR);

	return EXIT_SUCCESS;
}