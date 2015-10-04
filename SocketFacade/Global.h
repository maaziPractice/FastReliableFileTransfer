#include <iostream>
#include <queue>

#include<stdio.h>
#include <assert.h>
#include <semaphore.h>

#include <cstring>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<time.h>
using namespace std;


#define UDPDataSize 1500
#define UDPPayloadSize   1504 // 4 bytes for meta-data size while sending

#define UDPControlDataSize 100
#define ControllerBufferSize 100


#define fileTransferPort 4000


typedef struct
{
	int sockfd;
	struct addrinfo receiversAddressInfo;
	char bufferToBeSent[UDPPayloadSize];
	unsigned int sendingSize;
}SendSocket;


typedef struct
{
	int sockfd;
	struct sockaddr_storage receiversAddressInfo;
	char bufferReceived[UDPPayloadSize];
	unsigned int receivedDataSize;
}ReceiveSocket;


typedef struct
{
	int seqNoOfFileChunk;
	char pureChunkbytes[1500];
}SingleFileChunk;


/*queue<int> reTransmittQ;
sem_t  reTransmittQSemaphore ;

bool isFinish = false;*/

