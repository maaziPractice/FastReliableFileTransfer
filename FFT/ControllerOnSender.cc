#include <pthread.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "Global.h"

void Controller_Initializer()
{

	sockForControlPort = frft_create_socket();
	struct sockaddr_in serv_addr = get_self_server_address(portForController);
	frft_bind_socket(sockForControlPort,serv_addr);

}

void SendTheLostList(char * buf,unsigned int bufLen)
{
	// assert buflen % BytesConsumedBySeqNumber == 0
	//pthread_mutex_lock( &reTransmittQMutex );
	unsigned int max = bufLen/sizeof currentSeqNumber;
	assert(max < 301);
	assert(bufLen % sizeof currentSeqNumber == 0 );
	for (int var = 0; var < max; ++var)
	    {
	       // (   *  (unsigned int*)  (  (unsigned int*) buf + var)   );
	            unsigned int lostChunksSeqNumber = *  (unsigned int *) (buf +(var*sizeof currentSeqNumber));
	            printf("lost Chunk SeqNumber %u is ::   ", lostChunksSeqNumber);
	            assert(lostChunksSeqNumber < 7232 );
	            SendThisChunk(lostChunksSeqNumber);
	    }
	//pthread_mutex_unlock( &reTransmittQMutex );
}

int ReadOnControllSocket(char *controlBuffer)
{
	// TO DO: for Lab 4B
	struct sockaddr_in sockaddr_in_var;
	int returnValue = frft_recv_UDP(sockForControlPort,&sockaddr_in_var , controlBuffer,ControllerBufferSize);

	cout <<"\nRead one LostList\n";
	if(returnValue == -1)
		printf("\nError in ReadOnControllSocket from frft recev from\n");


	return returnValue;
}


void* ControllerOnSender(void *arg)
{
	Controller_Initializer();

	char controlBuffer[ControllerBufferSize] ;
	long int numBytesRead = -1;

	while(1)
	{
		numBytesRead = ReadOnControllSocket(controlBuffer);

		assert(numBytesRead <= ControllerBufferSize);
		// Assuming we can send an empty UDP packet
		if(numBytesRead > 0)
		{
                   SendTheLostList(controlBuffer,numBytesRead);
                   usleep(30);
		}
		else if(numBytesRead == 0)
		{
                             isFinish = true;
                             break;
		}
		else
			{
			    assert( 1==0 );
			}

	}

	pthread_exit(0);

}



