#include <iostream>
#include <queue>
#include <pthread.h>
#include <assert.h>
#include "Utilities.h"
#include "Global.h"
using namespace std;


void HandShakeInit()
    {



    }


void Controller_Initializer()
{
      //
	sockForControlPort = frft_create_socket();
	struct sockaddr_in serv_addr = get_self_server_address(portForController);
	frft_bind_socket(sockForControlPort,serv_addr);

}

void SendFileChunks_Initializer()
{



       isFinish = false;

	send_file_trans = fopen(FILE_NAME,"r");
	if(send_file_trans == NULL)	printf("Error: opening file\n");

	send_file_retrans = fopen(FILE_NAME,"r");
		if(send_file_retrans == NULL)	printf("Error: opening file\n");

	socketForTran = frft_create_socket();
	socketForReTran = frft_create_socket();

	// this is to get receivers port and IP address
	file_recv_addr = get_recv_address(RECEIVER_NODE,receiverPort);
	/*sockForControlPort =  frft_create_socket();
	frft_bind_socket(sockForControlPort,get_self_server_address());*/

	printf("\n Exiting Initializer");
}


void CleanUp()
{
    close(socketForTran);
    close(socketForReTran);
    fclose(send_file_trans);
    fclose(send_file_retrans);
}

void *SendFileChunks(void *)
{
	SendFileChunks_Initializer();

	int i=0;
	do
	{
		i=SendConsecutiveChunks ();
		//break;
	}while (i != -1 && i != -2);

	printf("Total packets sent is %u",totalPacketsSent);
	cout << "\n Total packets sent" << totalPacketsSent;
//		pthread_mutex_lock( &reTransmittQMutex );
//			unsigned int lostChunks[reTransmittQBurst] , i=1;
//			while (reTransmittQ.empty() == false || i <= reTransmittQBurst)
//			{
//				lostChunks[i]  = reTransmittQ.front();
//				reTransmittQ.pop();
//				i++;
//			}
//		pthread_mutex_unlock( &reTransmittQMutex );
//		while(i  > 0)
//		{
//                       SendThisChunk(lostChunks[i]);
//			i--;
//		}


	// when isFinish ==  true will reTransmittQ empty ??
   // & should I send some thing back to receiver when I receive FIN control message from it?
	//STOP all threads as well

	// need to wait for retrnasmission thread as well
	// CleanUp();
	pthread_exit(0);
}


