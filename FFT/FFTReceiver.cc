#include "Global.h"

int InitialisationReceiver()
{
	//numberOfPacketsRemaining = ceil(FILE_SIZE / ChunkSize);
	//create sockets for reading from wire
       cout <<"\n Init Receiver";
	starttime = time(NULL);
	maxSeqNoReceived = -1;
    // completelyDoneTill = 0;
    readFileChunkSock = frft_create_socket();
    frft_bind_socket(readFileChunkSock, get_self_server_address(receiverPort));
    //frft_recv_UDP(int sock_fd, struct sockaddr_in *sender_addr,char *buffer,int buffer_len);// have a option of passing the sender's address len as reference

    sendLostListSock = frft_create_socket();
    file_sender_addr = get_senders_address(SENDER_NODE,portForController);

    DEST_file_Handler = fopen(DEST_FILE_NAME,"w");
    if(DEST_file_Handler == NULL)	printf("Error: opening file for writing\n");

    printf("\n Exiting Receiver Init");

  cout << "\n Exit receiver";



    return 0;
}

void  readFileChunksFromWire(SingleFileChunk &singleFileChunk)
{
	// TO DO: for Lab 4B
	        struct sockaddr_in sockaddr_in_var;

		//cout << " In readFileChunksFromWire & value of singleFileChunk.actualFileChunkBytes is "<< singleFileChunk.actualFileChunkBytes;
	//	printf("\n Blocking on recvfrom in receiver ");

		int returnValue = frft_recv_UDP(readFileChunkSock, &sockaddr_in_var , singleFileChunk.actualFileChunkBytes ,ChunkSize+sizeof currentSeqNumber);
		//assert(returnValue > sizeof currentSeqNumber);

		/*if (totalPacketsRec == 0)
		{
		    file_sender_addr = sockaddr_in_var;
		    file_sender_addr.sin_port = htons(portForController);
		}*/

		if(returnValue == -1)
					printf("\nError in readFileChunksFromWire from frft recv from\n");
		totalPacketsRec++;

		//  cout << "Value of retrun value is "<<returnValue;


		singleFileChunk.actualChunkBytesReadFromWire = returnValue - sizeof currentSeqNumber;

		if(singleFileChunk.actualChunkBytesReadFromWire < 0) printf("\nCant happen readFileChunksFromWire\n");

       singleFileChunk.chunkSeqNumber =    * (unsigned int *) ( singleFileChunk.actualChunkBytesReadFromWire + (char *)singleFileChunk.actualFileChunkBytes) ;

  //     printf("\nreadFileChunksFromWire:singleFileChunk.chunkSeqNumber  %u and ChunkBytesCout is %u",singleFileChunk.chunkSeqNumber,singleFileChunk.actualChunkBytesReadFromWire );
}

void writeFileChunkToFile(SingleFileChunk &singleFileChunk)
{
	fseek(DEST_file_Handler, ChunkSize*singleFileChunk.chunkSeqNumber,SEEK_SET);
	frft_file_write(DEST_file_Handler,   singleFileChunk.actualFileChunkBytes, singleFileChunk.actualChunkBytesReadFromWire);
}

void* Receiver(void *)
{
	InitialisationReceiver();
        SingleFileChunk singleFileChunk;

  while(numberOfPacketsRemaining != 0)
   {
	    printf("\n In Receiver : %d",numberOfPacketsRemaining);
	   readFileChunksFromWire(singleFileChunk);
      //if(singleFileChunk.seqNoOfFileChunk - completelyDoneTill == 1) completelyDoneTill++;


	   printf("\n singleFileChunk.chunkSeqNumber  %u",singleFileChunk.chunkSeqNumber );
	  printf("\n maxSeqNoReceived %ld ",maxSeqNoReceived);
	  if(singleFileChunk.chunkSeqNumber+1 > maxSeqNoReceived+1)
		  {
				// Lock the Lost List
				pthread_mutex_lock( &lostListMutex );
				// Shaq:
						for (unsigned int var = maxSeqNoReceived+1 ; var <  singleFileChunk.chunkSeqNumber ; ++var)
						{
							/*mark all between current maxSeqNoReceived to singleFileChunk.seqNoOfFileChunk to
							as lost packets in lost-list */
							//assert(    LostList.find(var) == LostList.end()   );
							////assert(var < 7232);
							LostList.insert(var);
						}
				 pthread_mutex_unlock( &lostListMutex );
				// unLock the Lost List
				maxSeqNoReceived = singleFileChunk.chunkSeqNumber;
		//		printf("\n maxSeqNoReceived %ld ",maxSeqNoReceived);
				  // write this chunk to file on disk
				writeFileChunkToFile(singleFileChunk);
				numberOfPacketsRemaining-- ;

				//if(maxSeqNoReceived == 7231) fclose(DEST_file_Handler);
		//		printf("\n numberOfPacketsRemaining %u ",numberOfPacketsRemaining);
		  }
	  else
	  {
		  if(singleFileChunk.chunkSeqNumber == maxSeqNoReceived)
		  {
			  printf("\n First   drop the packet since it is duplicate \n");
		  }
		  else //singleFileChunk.chunkSeqNumber < maxSeqNoReceived
		  {
			  	  // Lock the Lost List
			       pthread_mutex_lock( &lostListMutex );
			       //assert(false);
							if(  LostList.find(singleFileChunk.chunkSeqNumber) != LostList.end() )    //    singleFileChunk.seqNoOfFileChunk IS IN in the Lost_List)
							{
								  /*remove it from the lost list since either it is retransmission
								  OR it is first transmission which is out of order*/
								  writeFileChunkToFile(singleFileChunk);
								  numberOfPacketsRemaining--;
								  LostList.erase (singleFileChunk.chunkSeqNumber);
							}
							else
							  printf("\nSecond:: drop the packet since it is duplicate %u \n",singleFileChunk.chunkSeqNumber);                        	// we have already got it, it is duplicate
                            pthread_mutex_unlock( &lostListMutex );
			    // unLock the Lost List
		  }

	  }

   }



       fclose(DEST_file_Handler);
       cout <<"\n\n\nTotal Packets Received is "<< totalPacketsRec;

       numberOfPacketsRemainingLS = numberOfPacketsRemaining;
       endtime = time(NULL);

       int time = endtime - starttime;

       printf("\n Time is %d",time);
       pthread_exit(0);
}




void EdgeCaseHandler()
    {
	time_t curr_time = time(NULL);
	if(         isFirstEntry == true  &&    curr_time - starttime  > (fileMetaData.timeInSecForTransfer)    )
	    {
	    	    if(numberOfPacketsRemaining > 0)
	    	     {
	    			 pthread_mutex_lock( &lostListMutex );
	    			 for (unsigned int var = maxSeqNoReceived+1 ; var <  globalMaxSeqNumber ; ++var)
	    							    {
	    								    LostList.insert(var);
	    							    }
	    			 pthread_mutex_unlock( &lostListMutex );
	    			 isFirstEntry = false;
	    	     }
	    	}
	else
	    return ;

    }

