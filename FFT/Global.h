#include <iostream>
#include <queue>
#include <pthread.h>
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
#include "frft_socket_api.h"
#include "Utilities.h"
#include <iostream>
#include <set>
#include<math.h>
using namespace std;


#define UDPDataSize 1500
#define UDPPayloadSize   1504 // 4 bytes for meta-data size while sending
#define UDPControlDataSize 100

#define normalSendQBurst 50
#define reTransmittQBurst 50



// Common to BOTH reciver and sender
#define ControllerBufferSize 1200  //also determines size of a max size NAK

// GLOBAL VARIABLE Sender START
#define FILE_SIZE 14500


#define normalSendQBurst 50
#define reTransmittQBurst 50
#define FILE_NAME "data.bin"
#define DEST_FILE_NAME "data2.bin"

#define MTUSize 1500
#define normalSendQBurst 50
#define reTransmittQBurst 50
#define ChunkSize 1450
/*unsigned int currentSeqNumber = 0;
short unsigned int BytesConsumedBySeqNumber = sizeof currentSeqNumber;

FILE *send_file_trans;
FILE *send_file_retrans;

queue<unsigned int> reTransmittQ;
pthread_mutex_t reTransmittQMutex = PTHREAD_MUTEX_INITIALIZER;

//no lock for this
bool isFinish = false;



int socketForTran;
int socketForReTran;
int sockForControlPort;
struct sockaddr_in file_recv_addr;


// GLOBAL VARIABLE Sender END



// GLOBAL VARIABLE Receiver START



 long int maxSeqNoReceived = -1;
int readFileChunkSock;
int sendLostListSock;
struct sockaddr_in file_sender_addr;

set<unsigned int> LostList;
set<unsigned int>::iterator LostListIterator;
pthread_mutex_t lostListMutex = PTHREAD_MUTEX_INITIALIZER;

FILE *DEST_file_Handler;
unsigned int numberOfPacketsRemaining;

// GLOBAL VARIABLE Receiver END

char file_name[50];
char send_buffer[MAX_SOCK_BUFF];
char recv_buffer[MAX_SOCK_BUFF];
FILE *send_file,*recv_file; */


// Socket Settings and Initialisation

#define receiverPort 4000  // for receiving data
#define senderPort   5555
extern int portForController; // for receiving controll data on sender


//#define RECEIVER_NODE "recNode"
//#define SENDER_NODE "sendNode"


#define MAX_SOCK_BUFF 1024


/* Extern defn start */
extern 	unsigned int currentSeqNumber;
extern 	unsigned int BytesConsumedBySeqNumber;
extern 	FILE *send_file_trans;
extern 	FILE *send_file_retrans;
extern 	queue<unsigned int> reTransmittQ;
extern 	pthread_mutex_t reTransmittQMutex;

extern 	bool isFinish ;
extern 	int socketForTran;
extern 	int socketForReTran;
extern 	int sockForControlPort;
extern 	struct sockaddr_in file_recv_addr;
extern 	long int maxSeqNoReceived;
extern 	int readFileChunkSock;
extern 	int sendLostListSock;
extern 	struct sockaddr_in file_sender_addr;
extern 	set<unsigned int> LostList;
extern 	set<unsigned int>::iterator LostListIterator;
extern 	pthread_mutex_t lostListMutex;
extern 	FILE *DEST_file_Handler;
extern 	unsigned int numberOfPacketsRemaining;
extern    unsigned int numberOfPacketsRemainingLS;

extern 	char file_name[50];
extern 	char send_buffer[MAX_SOCK_BUFF];
extern 	char recv_buffer[MAX_SOCK_BUFF];
extern 	FILE *send_file,*recv_file;
extern     char SENDER_NODE[];
extern     char RECEIVER_NODE[];

extern unsigned int totalPacketsRec;
extern unsigned int totalPacketsSent;

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
	unsigned int chunkSeqNumber;
	char actualFileChunkBytes[ChunkSize+sizeof currentSeqNumber];
	unsigned int actualChunkBytesReadFromWire;

}SingleFileChunk;






// Sender
void SendFileChunks_Initializer();
void* SendFileChunks(void *);
void* ControllerOnSender(void *);
void Controller_Initializer();
//
// Receiver
int InitialisationReceiver();
void* Receiver(void *);
void* LostListSender(void *);

//
