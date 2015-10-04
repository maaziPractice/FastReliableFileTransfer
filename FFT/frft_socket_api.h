//Includes for sockets
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h> 

#define MAX_SOCK_BUFF 1024
#define MAX_BUFF_SIZE 1024
#define MAX_SOCK_RECVBUFF 1024*1024*1024
#define RECV_PORTNO 5555
#define SENDER_PORTNO 4444
#define SERVER_IP_ADDR "10.1.1.2"
#define SLEEP_TIME 20
#define NUMBER_OF_PACKETS 1024*1024

typedef struct payload {
     unsigned int seq_num;
     char data[MAX_BUFF_SIZE];
}udp_payload;


extern char send_buffer[MAX_SOCK_BUFF];
extern char recv_buffer[MAX_SOCK_BUFF];
extern char file_read_buffer[MAX_SOCK_BUFF];
extern char file_write_buffer[MAX_SOCK_BUFF];
extern char sock_send_buffer[MAX_SOCK_BUFF];
extern char sock_recv_buffer[MAX_SOCK_BUFF];
extern FILE *send_file,*recv_file;

int frft_create_socket();
int frft_bind_socket(int, struct sockaddr_in);
int frft_send_UDP(int sock_fd, struct sockaddr_in recv_addr,char *buffer,int buffer_len);
int frft_recv_UDP(int sock_fd, struct sockaddr_in *sender_addr,char *buffer,int buffer_len);
int frft_file_read(FILE *, char *,int);
int frft_file_write(FILE *,char *,int);
struct sockaddr_in get_server_address(char *server_ip,int portno);
struct sockaddr_in  get_self_server_address(int portno);
struct sockaddr_in get_senders_address(char *server_ip,int portno);
struct sockaddr_in get_recv_address(char *server_ip,int portno);


