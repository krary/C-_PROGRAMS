#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<netdb.h>
#include<arpa/inet.h>
#ifndef LIBRARY_H
#define LIBRARY_H 


#define PORT 80
#define DATAGRAM_LEN 4096
typedef struct{
    struct iphdr *ip_hdr;
   	struct tcphdr *tcp_hdr;
   	char datagram[DATAGRAM_LEN];
   		
}Netcat;
void init_ip(Netcat*);
void init_tcp(Netcat*);




#endif
