#include "Global.h"



ReceiveSocket createSocketForReception(string portForListening)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	char s[INET6_ADDRSTRLEN];
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; // set to AF_UNSPEC to make IP agnostic
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	ReceiveSocket rSock;
	if ((rv = getaddrinfo(NULL, portForListening.c_str(), &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));

		// TO DO:
		return rSock;
	}
	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1)
		{
			perror(" createSocketForReception : socket creation");
			continue;
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(sockfd);
			perror("createSocketForReception : bind");
			continue;
		}
		break;
	}
	if (p == NULL)
	{
		fprintf(stderr, "createSocketForReception : failed to bind socket\n");
		// TO DO:
		return rSock;
	}
	freeaddrinfo(servinfo);
	//printf("createSocketForReception : waiting to recvfrom...\n");

	// TO DO: make entry some where for final clean up

	rSock.sockfd = sockfd ;
	return rSock;
}

SendSocket createSocketForSending(string ipOfReceiver,string portOnWhichReceiverListens)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	SendSocket s;
	if ((rv = getaddrinfo( ipOfReceiver.c_str() , portOnWhichReceiverListens.c_str(), &hints,
			&servinfo)) != 0)
	{
		fprintf(stderr, "createSocketForSending: getaddrinfo: %s\n",
				gai_strerror(rv));
		return s;
	}
	// loop through all the results and make a socket
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1)
		{
			perror("createSocketForSending : talker: socket");
			continue;
		}
		break;
	}
	if (p == NULL)
	{
		fprintf(stderr,
				"createSocketForSending : talker: failed to bind socket\n");
		return s;
	}

	//printf("createSocketForSending : Lets send now...\n");
	s.sockfd = sockfd;
	s.receiversAddressInfo = *p;

	return s;
}


int sendOnUDPSocket(SendSocket sendSocket)
{
	//printf("sendOnUDPSocket : Sending packets");
	int numbytes = 0;
	if ((numbytes = sendto(sendSocket.sockfd, (sendSocket.bufferToBeSent), sendSocket.sendingSize ,
			                                   0 , (sendSocket.receiversAddressInfo.ai_addr),
			                                   sendSocket.receiversAddressInfo.ai_addrlen)) == -1)
		{
			perror("sendOnUDPSocket  : sendto");
			exit(1);
		}
	return 0;
}


int receiveFromUDPSocket(ReceiveSocket &receiveSocket)
{
//	printf("receiveFromUDPSocket : receiving packets");
	socklen_t addr_len;
	addr_len = sizeof receiveSocket.receiversAddressInfo;
	if ((receiveSocket.receivedDataSize = recvfrom(receiveSocket.sockfd, (receiveSocket.bufferReceived), UDPPayloadSize, 0,
			(struct sockaddr *) &receiveSocket.receiversAddressInfo, &addr_len)) == -1)
	{
		perror(" receiveFromUDPSocket ");
		exit(1);
	}
	//receiveSocket.bufferReceived[receiveSocket.receivedDataSize] = '\0';
	//printf("listener: got packet from %s %d\n",receiveSocket.bufferReceived, receiveSocket.receivedDataSize);

	if(receiveSocket.receivedDataSize != 0)
	{
		printf("\n\n\n 1400 not matching!!!!!!!!!!!\n\n\n");
		exit(0);
	}

	return 0;
}

int sendConsecutiveChunks()
{
// TO DO:
	return 0;
}


int readFileChunksFromWire(SingleFileChunk &singleFileChunk)
{
// do checksumming as extra precaution







}


