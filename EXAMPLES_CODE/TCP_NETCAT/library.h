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

extern struct iphdr ip_header;
extern struct tcphdr tcp_header;
extern char datagram[DATAGRAM_LEN];
void init_ip(struct iphdr *);
void init_tcp(struct tcphdr *);
void init_datagram_ip_tcp(char*);



#endif
