#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <set>
 #include "Global.h"


 	unsigned int currentSeqNumber = 0;
 	unsigned int BytesConsumedBySeqNumber = sizeof currentSeqNumber;
 	FILE *send_file_trans;
 	FILE *send_file_retrans;
 	queue<unsigned int> reTransmittQ;
 	pthread_mutex_t reTransmittQMutex = PTHREAD_MUTEX_INITIALIZER;
 	//no lock for this
 	bool isFinish = false;
 	int socketForTran;
 	int socketForReTran;
 	int sockForControlPort;
 	int portForController=5000;
 	struct sockaddr_in file_recv_addr;
 	long int maxSeqNoReceived = -1;
 	int readFileChunkSock;
 	int sendLostListSock;
 	struct sockaddr_in file_sender_addr;
 	set<unsigned int> LostList;
 	set<unsigned int>::iterator LostListIterator;
 	pthread_mutex_t lostListMutex = PTHREAD_MUTEX_INITIALIZER;
 	FILE *DEST_file_Handler;
 	unsigned int numberOfPacketsRemaining=7232;
 	unsigned int numberOfPacketsRemainingLS=7232;
 	// GLOBAL VARIABLE Receiver END
 	char file_name[50];
 	char send_buffer[MAX_SOCK_BUFF];
 	char recv_buffer[MAX_SOCK_BUFF];
 	FILE *send_file,*recv_file;
 	char SENDER_NODE[] = "Client";
 	char RECEIVER_NODE[]="10.1.1.3";


 	unsigned int totalPacketsRec=0;
 	unsigned int totalPacketsSent=0;

void cleanTheMessUp(int s)
{
	// TO DO:
    printf("Program was trying to abort or terminate.");

}

int main(int argc, char* argv[])
{
	int server_flag = -1;
	int file_len;
	int err;
	pthread_t Receiver_thread,LostListSender_thread,ControllerOnSender_thread,SendFileChunks_thread;
	//char file_name[50];
	if(argc < 3)
	{
		printf("ERROR: missing arguments\n");
		return -1;
	}

	printf("\n Argumets : %s %s %s",argv[0],argv[1],argv[2]);
	if(strcmp(argv[1],"-s") == 0)
		server_flag = 1;
	else if(strcmp(argv[1],"-c") == 0)
		server_flag =  0;

	//file_len = strlen(argv[3]);
	strcpy(file_name,argv[2]);
	file_len = strlen(file_name);

	printf("\n FILE NAME : %s\n",file_name);

	if(server_flag == 1)
	{
		printf("\n CALLING RECEIVER\n\n");
		//InitialisationReceiver();


		err = pthread_create(&Receiver_thread, NULL,Receiver, NULL);
		if(err != 0) perror("Thread creation error");

		// Forking new threads
		err = pthread_create(&LostListSender_thread, NULL, LostListSender, NULL);
		if(err != 0) perror("Thread creation error");

		pthread_join(Receiver_thread, NULL);
		pthread_join(LostListSender_thread, NULL);

				exit(0);


	}
	else if(server_flag == 0)
	{
		printf("\n CALLING SENDER\n\n");

		Controller_Initializer();
		SendFileChunks_Initializer();

		// Forking new threads
		err = pthread_create(&ControllerOnSender_thread, NULL,ControllerOnSender, NULL);
		if(err != 0) perror("Thread creation error");

		err = pthread_create(&SendFileChunks_thread, NULL, SendFileChunks, NULL);
		if(err != 0) perror("Thread creation error");

	     pthread_join(ControllerOnSender_thread, NULL);

		//SendFileChunks(NULL);
		pthread_join(SendFileChunks_thread, NULL);

		exit(0);
	//	pid = fork();
	//	if(pid < 0)
//			printf("ERROR on fork\n");
//		if(pid == 0)
//		{
//			ack_receiver_function();
//			exit(0);
//		}
//		else
//			sender_function();

	}
	else
		printf("\n CALLING NOTHING");

}
