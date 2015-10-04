
#include "Global.h"
#include "SocketAPI.h"
#include <pthread.h>

void* receiver(void *ptr);
void* sender(void *ptr);


int main()
{

	printf("value of i is ");

	pthread_t thread_sender,thread_receiver;
		int i[2];
		i[0] = 0;
		i[1] = 1;

	int err =  pthread_create (&thread_receiver, NULL,receiver , (void *) &i[0]);
	if (err != 0)perror("thread creation error");

	int j=1;
	while(j<1000){
		j++;
		printf("");
	}

	printf("strating sender");
	err = pthread_create (&thread_sender, NULL, sender, (void *) &i[1]);
	if (err != 0)perror("thread creationerror");

	 pthread_join(thread_receiver, NULL);
	 pthread_join(thread_sender, NULL);

	 exit(0);
}


void* sender(void *ptr)
{
	printf("value of i is sender");

	SendSocket sendSocket = createSocketForSending("localhost","4000");

	int i=0;
	while(i<800)
	{
	  strcpy(sendSocket.bufferToBeSent,"HI this is mayur raleraskar           ");
	  sendSocket.sendingSize = 0;//strlen(sendSocket.bufferToBeSent) + 1;

	  sendOnUDPSocket(sendSocket);
	  int j=1;
	  	while(j<100){
	  		j++;
	  		pthread_yield();
	  	}
	  //printf("sender : after sending");

	   i++;
	}
	close(sendSocket.sockfd);
	pthread_exit(0);
}

void* receiver(void *ptr)
{

	printf("value of i is receiver");
	ReceiveSocket receiveSocket = createSocketForReception("4000");
	int i=0;
	while( i<800)
		{
		    receiveFromUDPSocket(receiveSocket);
	//	    printf("****** %s ******  \n",receiveSocket.bufferReceived);
		    i++;
		}
	printf("\n\n\n\n\nvalue of i is %d, & length is %d", i,receiveSocket.receivedDataSize);
	pthread_exit(0);
}

