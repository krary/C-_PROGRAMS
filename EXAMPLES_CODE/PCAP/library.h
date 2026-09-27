#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<pcap.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<pcap.h>
#include<ctype.h>
#ifndef LIBRARY_H
#define LIBRARY_H


//PCAP_ERRBUF_SIZE = 256 
//BUFSIZ           = 8192



typedef struct{

	pcap_t *handle;
	struct pcap_pkthdr header;

	char error_buffer[PCAP_ERRBUF_SIZE];
    const u_char *packet;
	

}PCap_info;

void open_interface(PCap_info*);
void capture_packet(PCap_info*);
void reading_packet_ascii(PCap_info*);



#endif
