//#include "Global.h"
//
//
//
//void  readFileChunksFromWire(SingleFileChunk &singleFileChunk)
//{
//	// TO DO: for Lab 4B
//		struct sockaddr_in sockaddr_in_var;
//		int returnValue = frft_recv_UDP(readFileChunkSock, &sockaddr_in_var , singleFileChunk.actualFileChunkBytes ,ChunkSize+sizeof currentSeqNumber);
//
//		if(returnValue == -1)
//			printf("\nError in readFileChunksFromWire from frft recev from\n");
//
//		singleFileChunk.actualChunkBytesReadFromWire = returnValue - sizeof currentSeqNumber;
//
//		if(singleFileChunk.actualChunkBytesReadFromWire < 0) printf("\nCant happen readFileChunksFromWire\n");
//
//       singleFileChunk.chunkSeqNumber =    * (unsigned int *) ( singleFileChunk.actualChunkBytesReadFromWire + (char *)singleFileChunk.actualFileChunkBytes) ;
//}
//
//void writeFileChunkToFile(SingleFileChunk &singleFileChunk)
//{
//	fseek(DEST_file_Handler, ChunkSize*singleFileChunk.chunkSeqNumber,SEEK_SET);
//	frft_file_write(DEST_file_Handler,   singleFileChunk.actualFileChunkBytes, singleFileChunk.actualChunkBytesReadFromWire);
//}
