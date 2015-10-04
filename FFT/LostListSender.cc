#include "Global.h"

void SendThisNAK(char *NAK,int numberOfSeqNumber)
{
         //assert( ( numberOfSeqNumber*sizeof currentSeqNumber)  <= ControllerBufferSize);
	frft_send_UDP(sendLostListSock , file_sender_addr ,NAK ,numberOfSeqNumber*sizeof currentSeqNumber);
	//cout <<"\nSent one LostList\n";
}

void* LostListSender(void *arg)
{
    while(numberOfPacketsRemainingLS != 0)
	{
	    pthread_mutex_lock( &lostListMutex );
	    cout <<"\nAbout Send one LostList\n";

	    int i=0;
	    char NAK[ControllerBufferSize];
	    //assert(BytesConsumedBySeqNumber == sizeof currentSeqNumber);
	    assert(  LostList.size() < 75000);

	    for ( set<unsigned int>::iterator it=LostList.begin() ; it != LostList.end(); it++ )
	    {
		    *  (unsigned int *) (NAK +(i*BytesConsumedBySeqNumber)) = *it;
		    //assert(*  (unsigned int *) (NAK +(i*BytesConsumedBySeqNumber))    < 7232) ;
		    i++;

		    if(i == ( ControllerBufferSize / sizeof currentSeqNumber))
		    {
			    //assert(i < 301);
			    SendThisNAK(NAK,i);
			    i=0;
		    }
	    }
	    if(i>0) SendThisNAK(NAK,i);
	    pthread_mutex_unlock( &lostListMutex );

	    usleep(1000 *1300);


	}


    cout << " Sending FIN";
    SendThisNAK( NULL,0);
    SendThisNAK( NULL,0);
    SendThisNAK( NULL,0);
    SendThisNAK( NULL,0);
    SendThisNAK( NULL,0);

    pthread_exit(0);
}


