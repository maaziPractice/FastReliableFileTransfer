#include "Global.h"


void writeSequenceNumber(char *arr,unsigned int numberToWrite)
{
		*(unsigned int *) (arr) = numberToWrite ;
}

int SendConsecutiveChunks ()
{

    char singleFileChunk[ChunkSize+sizeof currentSeqNumber];
    int actualBytesRead=-2;

	for (int var = 0; var < normalSendQBurst; ++var)
	{
	   // assert();
		actualBytesRead = frft_file_read(send_file_trans, singleFileChunk, ChunkSize);
		//cout <<"actualBytesRead+BytesConsumedBySeqNumber "<<;
		if(actualBytesRead > 0)
		{
			// ASSERT(actualBytesRead == ChunkSize);
			//printf("\n Sending files to receiver var = %d",var);
			/*for (long unsigned int var = 0; var < 100000; ++var) {
				pthread_yield();
			}*/

		        usleep(400);
			writeSequenceNumber(singleFileChunk+actualBytesRead,currentSeqNumber);
			frft_send_UDP(socketForTran , file_recv_addr ,singleFileChunk ,actualBytesRead+BytesConsumedBySeqNumber);


			 currentSeqNumber++;
			 totalPacketsSent++;
			// if(currentSeqNumber == 7132)
			// 			    cout << "ActualBytesChunk are & currentSeqNumber"<<actualBytesRead <<"   "<<currentSeqNumber;

			 //REMOVE:

		}
		else if(actualBytesRead < 0)  	 { printf("\n\nSendConsecutiveChunks: End of Error Occurred while reading the file \n\n");break;}
	}

	return actualBytesRead;
}

// TO DO:
int  SendThisChunk(unsigned int lostChunksSeqNumber)
{
	char singleFileChunk[ChunkSize+sizeof currentSeqNumber];
	int actualBytesRead=-2;

	fseek(send_file_retrans,ChunkSize*lostChunksSeqNumber,SEEK_SET);
	actualBytesRead = frft_file_read(send_file_retrans, singleFileChunk, ChunkSize);
			//cout <<"actualBytesRead+BytesConsumedBySeqNumber "<<;
			if(actualBytesRead > 0)
			{
				// ASSERT(actualBytesRead == ChunkSize);
				//printf("\n Sending files to receiver var = %d",var);
				/*for (long unsigned int var = 0; var < 15000; ++var) {
					pthread_yield();
				}*/

				writeSequenceNumber(singleFileChunk+actualBytesRead,lostChunksSeqNumber);
				frft_send_UDP(socketForTran , file_recv_addr ,singleFileChunk ,actualBytesRead+BytesConsumedBySeqNumber);
			}
			else if(actualBytesRead < 0)  	 { printf("\n\n SendThisChunk: End of Error Occurred while reading the file \n\n");}
	return actualBytesRead;
}


