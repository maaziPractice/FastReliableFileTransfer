//File handling APIs
//This should include all the functions/APIs for file reading and 
//writing from and to the buffer and eventually to packet
#include <stdio.h>
#include <stdlib.h>
#include "frft_socket_api.h"


//char file_read_buffer[MAX_SOCK_BUFF];
//char file_write_buffer[MAX_SOCK_BUFF];
//FILE *sendfp,*recvfp;


int frft_file_read(FILE *sendfile,char *buffer,int buffer_len)
{
	
	//char *read_fb = send_buffer;
	int fread_result;
	//think of differnt function for this
	fread_result = fread((void *) buffer,1,buffer_len, sendfile);
	if (fread_result != buffer_len)
	{
		if(!feof(sendfile))
		{
			printf("File IO: Error in file read\n");
			return -2; //replace this -1 by error symbol
		} else
		{
			printf("File IO: End of file reached\n");
			//buffer_len = fread_result;
			if(fread_result == 0)
			    return -1;
		}
	}
//	printf("file buffer :%s\n\n\n",read_fb);
	//memcpy((void *) buffer,(void *)read_fb,buffer_len);
	return fread_result;
}

int frft_file_write(FILE *recvfile,char *buffer, int buffer_len)
{
	int fwrite_result;
	//char *write_fb = recv_buffer;
	
//	memcpy((void *) write_fb,(void *)buffer,buffer_len);
	
	fwrite_result = fwrite((void *) buffer,1,buffer_len,recvfile);
	if(fwrite_result != buffer_len)
	{
		printf("File IO: Error in file write\n");
		return -1; //replace this -1 by error symbol
	}
	return fwrite_result;
}

