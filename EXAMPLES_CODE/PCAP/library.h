#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<pcap.h>
#include<string.h>
#include<signal.h>

#include<netinet/if_ether.h>
#include<netinet/ip.h>
#include<netinet/ip_icmp.h>
#include<netinet/tcp.h>
#include<netinet/udp.h>


#include<arpa/inet.h>
#include<pcap.h>
#include<ctype.h>
#ifndef LIBRARY_H
#define LIBRARY_H

extern void protocols;

//PCAP_ERRBUF_SIZE = 256 
//BUFSIZ           = 8192



typedef struct{
    uint8_t option;
    pcap_if_t *alldevs;
	pcap_t *handle;
	struct pcap_pkthdr header;
	struct ether_header *ether;
    struct iphdr *ip_hdr;
    struct udphdr *udp_hdr;
    struct tcphdr *tcp_hdr;
    struct icmphdr *icmp_hdr;
    struct protocols *p;
    struct bpf_program bpf_p;
	char error_buffer[PCAP_ERRBUF_SIZE];
	char src_IP[INET_ADDRSTRLEN];
	char dst_IP[INET_ADDRSTRLEN];
	size_t l4_len;
    const u_char *packet;
	

}PCap_info;


typedef struct protocols{
	void (*init_struct_tcphdr)(PCap_info*);
	void (*init_struct_udphdr)(PCap_info*);
	void (*init_struct_icmphdr)(PCap_info*);
	void (*reading_info)(PCap_info*);
	uint8_t protocol;
}Protocols;

void open_interface(PCap_info*);
void capture_packet(PCap_info*);
void reading_packet_ascii(PCap_info*);
void init_struct_ethernet(PCap_info*);
void reading_packet_ethernet_MAC(PCap_info*);
void reading_packet_ethernet_type(PCap_info*);
void reading_packet_iphdr(PCap_info *p);
void reading_packet_tcphdr(PCap_info *p);
void reading_packet_udphdr(PCap_info *p);
void reading_packet_icmphdr(PCap_info *p);
void init_struct_iphdr(PCap_info *);
void init_struct_tcpphdr(PCap_info *);
void init_struct_udphdr(PCap_info *);
void init_struct_icmphdr(PCap_info *);
void init_struct_Protocols(Protocols*,PCap_info*);
void init_packet_callback(u_char *,const struct pcap_pkthdr *, const u_char *);
void init_packet_pcapift(PCap_info*);
void start_capture_loop(PCap_info*,int);
void reading_packet_payload(PCap_info *);
int init_packet_bpf(PCap_info *,const char *);
#endif
