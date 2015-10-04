/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}
void dostuff(int newsockfd)
{
	int n=0;
	char buffer[256];

	n = read(newsockfd,buffer,255);
	if (n < 0) error("ERROR reading from socket");
	printf("Here is the message: %s\n",buffer);
	n = write(newsockfd,"I got your message",18);
	if (n < 0) error("ERROR writing to socket");
	close(newsockfd);
}


int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr,from;
	int n;
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}


	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	fromlen = sizeof(struct sockaddr_in);
	while (1)
	{
		n = recvfrom(sockfd,buffer,255,0,(struct sockaddr *)&from,sizeof(from));
		if (n < 0) error("recvfrom");
		buf[n] = '\0';
		printf("\nMessage from the client is %s\n",buf);
		n = sendto(sock,"Got your message",17,0,(struct sockaddr *) &from,sizeof(from));
		if (n < 0)
			error("send  to");
	}

return 0;

}
