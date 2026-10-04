#include "library.h"


// ABRIR LA INTERFAZ 



                         /*open_interface*/
//===============================================================================
void open_interface(PCap_info* p){
	p->handle = pcap_open_live("wlxd8448953edc3",BUFSIZ,1,1000,p->error_buffer);
	if(p->handle==NULL){printf("ERROR %s\n",p->error_buffer);return;}

	printf("[EXIT] THE PROGRAM HAS CONNECT WITH THE KERNEL\n");
	
}
//================================================================================




                         /*capture_packet*/
//===================================================================================
void capture_packet(PCap_info *p){
	p->packet = pcap_next(p->handle,&p->header);
	if(p->packet == NULL){
		printf("THE PROGRMA CANNOT CAPTURE ANY PACKET PLEASE TRY LATTER...\n");return ;}
	else{
		printf("[+]NUMERO DE BYTE CAPTURADOS : %d\n",p->header.caplen);
		printf("[+]NUMERO REAL DE BYTES EN EL CABLE : %d\n",p->header.len);


	for(size_t x = 0; x < p->header.caplen; x++){
		printf("%02X ",p->packet[x]);
		if((x + 1) % 16 == 0)printf("\n");}}
printf("\n");}

//=====================================================================================



                    /*reading_packet_ascii*/
//=====================================================================================
void reading_packet_ascii(PCap_info *p){
	for(size_t x = 0; x < p->header.caplen;x++){
		u_char c = p->packet[x];
		if(isprint(c)){
			printf("%c",c);}
		else{
			printf(".");
		}
	}
printf("\n");
}




       				/*ESTRUCTURA Ethernet*/
//**************************************************************************************
void init_struct_ethernet(PCap_info *p){
	p->ether = (struct ether_header*)p->packet;}
//======================================================================================





//========================Reading info from the struct ether_header===================================
void reading_packet_ethernet_MAC(PCap_info *p){
   if(p == NULL){printf("Cann not read the Struct PCap plea check noch einmal...\n");return;}
    printf("MAC DESTINO: [");
	for(size_t x = 0; x < 6;++x){printf("%02X:",p->ether->ether_dhost[x]);}
    printf("]\n");


    printf("MAC ORIGEN: [");
	for(size_t x = 0; x < 6;++x){printf("%02X:",p->ether->ether_shost[x]);}
    printf("]\n");}
//*******************************************************************************************





//========================Reading info from the struct ether_header===================================
void reading_packet_ethernet_type(PCap_info *p){
    printf("VALUE OF ether_type  BEFORE TO CALL THE FUNCTION nthos [%04X]\n",p->ether->ether_type);
	uint16_t type = ntohs(p->ether->ether_type);
	printf("VALUE OF ether_type  AFTER TO CALL THE FUNCTION nthos [%04X]\n",type);



	switch(type){
		case ETHERTYPE_ARP:  printf("[ARP]\n"); break;
		case ETHERTYPE_IP:   printf("[IP]\n"); break;
		case ETHERTYPE_IPV6: printf("[IPV6]\n"); break;
		default            : printf("[OTHER TYPE]\n"); break;
			
	}
	
}
//*********************************************************************************************************




void init_struct_iphdr(PCap_info *p){
    if((ntohs(p->ether->ether_type)) == ETHERTYPE_IP){

    	p->ip_hdr = (struct iphdr*)(p->packet + sizeof(struct ether_header));
    	
	}
}


void reading_packet_iphdr(PCap_info *p){
	if((ntohs(p->ether->ether_type)) == ETHERTYPE_IP){
		inet_ntop(AF_INET,&(p->ip_hdr->saddr),p->src_IP,INET_ADDRSTRLEN);
		inet_ntop(AF_INET,&(p->ip_hdr->daddr),p->dst_IP,INET_ADDRSTRLEN);
		printf("IP FUENTE: %s\n",p->src_IP);
		printf("IP DESTINO: %s\n",p->dst_IP);

		if(p->ip_hdr->protocol == IPPROTO_TCP){printf("PROTOCOLO : TCP\n");}
		if(p->ip_hdr->protocol == IPPROTO_UDP){printf("PROTOCOLO : UDP\n");}
		if(p->ip_hdr->protocol == IPPROTO_ICMP){printf("PROTOCOLO : ICMP\n");}
	}
}
void reading_packet_tcphdr(PCap_info*p){
	if(p->tcp_hdr !=NULL){
		uint16_t src_port = ntohs(p->tcp_hdr->th_sport);
		uint16_t drc_port = ntohs(p->tcp_hdr->th_dport);
		printf("[TCP]PUERTO DE ORIGEN : %u\n",src_port);
		printf("[TCP]PUERTO DE DESTINO : %u\n",drc_port);
		printf("[FLAGS ] ACK: %u SYN: %u FIN: %u RST: %u\n",p->tcp_hdr->ack,p->tcp_hdr->syn,p->tcp_hdr->fin,p->tcp_hdr->rst);
		
	}
}
void reading_packet_udphdr(PCap_info*p){
	if(p->udp_hdr !=NULL){
		uint16_t src_port = ntohs(p->udp_hdr->uh_sport);
		uint16_t drc_port = ntohs(p->udp_hdr->uh_dport);
		printf("[UDP ]PUERTO DE ORIGEN : %u\n",src_port);
		printf("[UDP ]PUERTO DE DESTINO : %u\n",drc_port);
		}
}
void reading_packet_icmphdr(PCap_info *p){
	if (p->icmp_hdr != NULL) {
	        printf("[ICMP] TIPO: %u | CODIGO: %u\n", p->icmp_hdr->type, p->icmp_hdr->code);
	        if (p->icmp_hdr->type == ICMP_ECHOREPLY) printf("       -> Echo Reply (Ping Response)\n");
	        else if (p->icmp_hdr->type == ICMP_ECHO) printf("       -> Echo Request (Ping Request)\n");
	    }
}


void init_struct_tcphdr(PCap_info *p){
	p->tcp_hdr = (struct tcphdr*)(p->packet + (sizeof(struct ether_header) + p->ip_hdr->ihl*4));}

void init_struct_udphdr(PCap_info *p){
	p->udp_hdr = (struct udphdr*)(p->packet + (sizeof(struct ether_header) + p->ip_hdr->ihl*4));}

void init_struct_icmphdr(PCap_info *p){
	p->icmp_hdr = (struct icmphdr*)(p->packet + (sizeof(struct ether_header) + p->ip_hdr->ihl*4));}

void init_struct_Protocols(Protocols *p,PCap_info *pc){
    
	if(pc->ip_hdr->protocol == IPPROTO_TCP){p->init_struct_tcphdr = init_struct_tcphdr; p->protocol = IPPROTO_TCP;p->reading_info = reading_packet_tcphdr;}
	if(pc->ip_hdr->protocol == IPPROTO_UDP){p->init_struct_udphdr = init_struct_udphdr; p->protocol = IPPROTO_UDP;p->reading_info = reading_packet_udphdr;}
	if(pc->ip_hdr->protocol == IPPROTO_ICMP){p->init_struct_icmphdr = init_struct_icmphdr; p->protocol = IPPROTO_ICMP;p->reading_info= reading_packet_icmphdr;}

	if(p->protocol != 0){
		switch(p->protocol){
			case IPPROTO_TCP: init_struct_tcphdr(pc);reading_packet_tcphdr(pc);pc->l4_len = pc->tcp_hdr->th_off *4;break;
			case IPPROTO_UDP: init_struct_udphdr(pc);reading_packet_udphdr(pc);pc->l4_len = sizeof(struct udphdr);break;
			case IPPROTO_ICMP: init_struct_icmphdr(pc);reading_packet_icmphdr(pc);pc->l4_len = sizeof(struct icmphdr);break;}}
			}
void reading_packet_payload(PCap_info *p){
    if(p->ip_hdr == NULL)return;
    size_t ip_len = p->ip_hdr->ihl *4;
    size_t ether_len = sizeof(struct ether_header);
    size_t total_len = ip_len + ether_len + p->l4_len;

    printf("EL TOTAL DE BYTE DE CABEZERAS ES DE : %zu \n",total_len);
    printf("Y EL TOTAL DE BYTE CAPTURADOS ES DE  : %u \n",p->header.caplen);
    if(p->header.caplen > total_len){
    	const u_char *ptr_payload = p->packet + total_len;
    	size_t payload_len = p->header.caplen - total_len;
    	printf("EL NUMERO DE BYTE DE LA CARGA O PAYLOAD ES DE %zu\n",payload_len);

    	for(size_t i = 0; i < payload_len; i++) {
    	            printf("%02X ", ptr_payload[i]);
    	            if ((i + 1) % 16 == 0 || i == payload_len - 1) {
    	                // Espaciado estético para alinear el texto ASCII
    	                if (i == payload_len - 1 && (i + 1) % 16 != 0) {
    	                    for (size_t pad = 0; pad < 16 - ((i + 1) % 16); pad++) printf("   ");
    	                }
    	                printf(" | ");
    	                size_t start = i - (i % 16);
    	                for (size_t j = start; j <= i; j++) {
    	                    printf("%c", isprint(ptr_payload[j]) ? ptr_payload[j] : '.');
    	                }
    	                printf("\n");}}}}

void init_packet_callback(u_char *data,const struct pcap_pkthdr *hdr , const u_char *bytes_crudos){
	PCap_info *p = (PCap_info *)data;
	p->header = *hdr;
	p->packet = bytes_crudos;

/*	p->ip_hdr = NULL;
	p->tcp_hdr = NULL;
	p->udp_hdr = NULL;
	p->icmp_hdr = NULL;
	//p->l4_len = 0;*/
	reading_packet_ascii(p);
	init_struct_ethernet(p);
	reading_packet_ethernet_MAC(p);
	reading_packet_ethernet_type(p);
	init_struct_iphdr(p);
	reading_packet_iphdr(p);
	init_struct_Protocols(p->p,p);
	reading_packet_payload(p);
	
}
void start_capture_loop(PCap_info*p,int packet_count){
	if(pcap_loop(p->handle,packet_count,init_packet_callback,(u_char*)p)< 0){
		printf("[ERROR] durante la captura de el loop  \n");
	}
}
